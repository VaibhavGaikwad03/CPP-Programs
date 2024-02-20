#include <linux/slab.h>
#include <linux/compat.h>
#include <linux/uaccess.h>
#include <linux/iversion.h>
#include "fat.h"
#define FAT_MAX_SHORT_SIZE	((MSDOS_NAME + 1) * NLS_MAX_CHARSET_SIZE + 1)
#define FAT_MAX_UNI_CHARS	((MSDOS_SLOTS - 1) * 13 + 1)
#define FAT_MAX_UNI_SIZE	(FAT_MAX_UNI_CHARS * sizeof(wchar_t))

static inline unsigned char fat_tolower(unsigned char c)
{
	return ((c >= 'A') && (c <= 'Z')) ? c+32 : c;
}

static inline loff_t fat_make_i_pos(struct super_block *sb,
				    struct buffer_head *bh,
				    struct msdos_dir_entry *de)
{
	return ((loff_t)bh->b_blocknr << MSDOS_SB(sb)->dir_per_block_bits)
		| (de - (struct msdos_dir_entry *)bh->b_data);
}

static inline void fat_dir_readahead(struct inode *dir, sector_t iblock,
				     sector_t phys)
{
	struct super_block *sb = dir->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *bh;
	int sec;

	/* This is not a first sector of cluster, or sec_per_clus == 1 */
	if ((iblock & (sbi->sec_per_clus - 1)) || sbi->sec_per_clus == 1)
		return;
	/* root dir of FAT12/FAT16 */
	if (!is_fat32(sbi) && (dir->i_ino == MSDOS_ROOT_INO))
		return;

	bh = sb_find_get_block(sb, phys);
	if (bh == NULL || !buffer_uptodate(bh)) {
		for (sec = 0; sec < sbi->sec_per_clus; sec++)
			sb_breadahead(sb, phys + sec);
	}
	brelse(bh);
}

static int fat__get_entry(struct inode *dir, loff_t *pos,
			  struct buffer_head **bh, struct msdos_dir_entry **de)
{
	struct super_block *sb = dir->i_sb;
	sector_t phys, iblock;
	unsigned long mapped_blocks;
	int err, offset;

next:
	brelse(*bh);
	*bh = NULL;
	iblock = *pos >> sb->s_blocksize_bits;
	err = fat_bmap(dir, iblock, &phys, &mapped_blocks, 0, false);
	if (err || !phys)
		return -1;	/* beyond EOF or error */

	fat_dir_readahead(dir, iblock, phys);

	*bh = sb_bread(sb, phys);
	if (*bh == NULL) {
		fat_msg_ratelimit(sb, KERN_ERR,
			"Directory bread(block %llu) failed", (llu)phys);
		/* skip this block */
		*pos = (iblock + 1) << sb->s_blocksize_bits;
		goto next;
	}

	offset = *pos & (sb->s_blocksize - 1);
	*pos += sizeof(struct msdos_dir_entry);
	*de = (struct msdos_dir_entry *)((*bh)->b_data + offset);

	return 0;
}

static inline int fat_get_entry(struct inode *dir, loff_t *pos,
				struct buffer_head **bh,
				struct msdos_dir_entry **de)
{
	/* Fast stuff first */
	if (*bh && *de &&
	   (*de - (struct msdos_dir_entry *)(*bh)->b_data) <
				MSDOS_SB(dir->i_sb)->dir_per_block - 1) {
		*pos += sizeof(struct msdos_dir_entry);
		(*de)++;
		return 0;
	}
	return fat__get_entry(dir, pos, bh, de);
}

static int uni16_to_x8(struct super_block *sb, unsigned char *ascii,
		       const wchar_t *uni, int len, struct nls_table *nls)
{
	int uni_xlate = MSDOS_SB(sb)->options.unicode_xlate;
	const wchar_t *ip;
	wchar_t ec;
	unsigned char *op;
	int charlen;

	ip = uni;
	op = ascii;

	while (*ip && ((len - NLS_MAX_CHARSET_SIZE) > 0)) {
		ec = *ip++;
		charlen = nls->uni2char(ec, op, NLS_MAX_CHARSET_SIZE);
		if (charlen > 0) {
			op += charlen;
			len -= charlen;
		} else {
			if (uni_xlate == 1) {
				*op++ = ':';
				op = hex_byte_pack(op, ec >> 8);
				op = hex_byte_pack(op, ec);
				len -= 5;
			} else {
				*op++ = '?';
				len--;
			}
		}
	}

	if (unlikely(*ip)) {
		fat_msg(sb, KERN_WARNING,
			"filename was truncated while converting.");
	}

	*op = 0;
	return op - ascii;
}

static inline int fat_uni_to_x8(struct super_block *sb, const wchar_t *uni,
				unsigned char *buf, int size)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	if (sbi->options.utf8)
		return utf16s_to_utf8s(uni, FAT_MAX_UNI_CHARS,
				UTF16_HOST_ENDIAN, buf, size);
	else
		return uni16_to_x8(sb, buf, uni, size, sbi->nls_io);
}
