/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:10:29 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/27 17:21:04 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_FT_LS_H
# define FT_LS_FT_LS_H

# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft.h"
# include "ft_printf.h"

# define INC max_len = 0; get_maxlen(path, &max_len, &i);
# define COLOUR color = DEFAULT; access = ft_strnew(11);
# define N_DOTS(str) (NOT_DOT(str) && (NOT_D_DOT(str)))
# define NOT_DOT(str) ((str[0] != '.') && (str[1] != 0))
# define NOT_D_DOT(str) ((str[0] != '.') && (str[1] != '.') && (str[2] != 0))
# define SWAP_LIST swap_string(&((*list)[i]), &((*list)[j]));
# define SWAP_COLOUR swap_string(&((*color_files)[i]), &((*color_files)[j]));
# define SWAP_STAT swap_stat_s(&mas[i], &mas[j]);
# define SWAP_L_C {SWAP_LIST SWAP_COLOUR}
# define SWAP_S_L_C {SWAP_STAT SWAP_LIST SWAP_COLOUR}
# define ELSE_IF_SET_FLAG(symb,FLAG) else if (sym == (symb)) *flag |= (FLAG)
# define FORM_T_1_1 buffer[3] = ' '; buffer[5] = temp[7]; buffer[6] = ' ';
# define FORM_T_1_2 buffer[4] = (char)((temp[6] == '0') ? (' ') : (temp[6]));
# define FORM_T_1 {FORM_T_1_1 FORM_T_1_2};
# define FORM_T_2_1 buffer[7] = ' '; buffer[8] = temp[0]; buffer[9] = temp[1];
# define FORM_T_2_2 buffer[10] = temp[2]; buffer[11] = temp[3];
# define FORM_T_2 {FORM_T_2_1 FORM_T_2_2}
# define T_TEMP(i) buffer[(i)] = (char)(t_temp % 10 + '0');
# define FORM_T_3_1 t_temp = (u_int)(sec / 3600); sec -= t_temp*3600; T_TEMP(8)
# define FORM_T_3_2 t_temp /= 10; T_TEMP(7) t_temp = (u_int)(sec / 60);
# define FORM_T_3_3 buffer[9] = ':'; T_TEMP(11) t_temp /= 10; T_TEMP(10)
# define FORM_T_3 {FORM_T_3_1 FORM_T_3_2 FORM_T_3_3}
# define G_C_RESET {g_c_files = 0; g_c_dirs = 0;}
# define PR_DIR_INIT IF_DIRV *i = 0; str = NULL;
# define IF_GWF if (!file_exist(str)) continue ;
# define IF_DIRI_1 {print_permission_denied(ft_strrchr(path, '/')); return (0);}
# define IF_DIRI dir = opendir(path); if (!dir) IF_DIRI_1
# define IF_DIRV_1 {print_permission_denied(ft_strrchr(path, '/')); return ;}
# define IF_DIRV dir = opendir(path); if (!dir) IF_DIRV_1
# define CH_NULL_STR(str,add) (str == NULL) ? (0) : (ft_strlen(str->add))

# define FLAG_ML 0x0001
# define FLAG_MA 0x0002
# define FLAG_MR 0x0004
# define FLAG_MT 0x0008
# define FLAG_R 0x0010
# define FLAG_MU 0x0020
# define FLAG_A 0x0040
# define FLAG_C 0x0080
# define FLAG_L 0x0100
# define FLAG_G 0x0200
# define FLAG_MF 0x0400
# define FLAG_U 0x0800
# define FLAG_MG 0x1000
# define FLAG_MD 0x2000

# define FR_BLACK "\e[0;30m"
# define FR_RED "\e[0;31m"
# define FR_GREEN "\e[0;32m"
# define FR_BLACK_BG_GREEN "\e[42;30m"
# define FR_YELLOW "\e[0;33m"
# define FR_BLUE "\e[0;34m"
# define FR_PURPLE "\e[0;35m"
# define FR_CYAN "\e[0;36m"
# define FR_WHITE_BG_BLUE "\e[44;37m"
# define FR_WHITE "\e[0;37m"
# define FR_LNK "\e[01;36m"
# define FR_SOCK "\e[01;35m"
# define DEFAULT "\e[0;0m"
# define BG_YELLOW_FR_BLACK "\e[30;103m"

u_int			g_flags;

typedef struct	s_format
{
	u_int		len_nlink;
	u_int		len_size;
	size_t		len_user;
	size_t		len_group;
	u_int		total_size;
}				t_format;

typedef struct	s_union
{
	u_int		len_nlink;
	u_int		len_size;
	u_int		len_user;
	u_int		i;
	size_t		len_group;
	size_t		total_size;
}				t_union;

void			print_file(char **file, u_int flags, u_int size);
int				print_long_output(const char *path, char **list,
					unsigned int num, char **color_files);
char			*get_ls_date(time_t *sec);
int				manage_flags(const char *str, u_int *flag);
void			sort_alpha(char ***list, const u_int size);
void			sort(const char *path, char ***list, const u_int size,
					char ***color_files);
void			sort_flag_u(const char *path, char ***list,
					const u_int size, char ***color_files);
void			sort_files(char ***list, const u_int size, u_int flags);
void			reverse(char ***list, const u_int size, char ***color_files);
void			print_output_color(char **list, unsigned int num,
					unsigned int max_len, char **color_files);
void			print_output(char **list, unsigned int num,
					unsigned int max_len);
void			print_long_output_file(char **list, unsigned int num,
					u_int flags);
int				analise_entry(char *name);
void			recursive_print_output(char **list, unsigned int num,
					unsigned int max_len, int flag);
void			respec_flags(void);
char			*respec_color(u_int type);

void			recursive_sort_alpha(char ***list, const u_int size);
void			recursive_sort_files(char ***list, const u_int size);
void			recursive_sort(const char *path, char ***list,
					const u_int size);
void			recursive_reverse(char ***list, const u_int size);
void			recursive_print_long_output_file(char **list,
					unsigned int num);
void			recursive_print_long_output(const char *path, char **list,
					unsigned int num, u_int flags);
void			color_sort_alpha(char ***list, const u_int size,
					char ***color_files);
char			*respec_color_part_two(char *str);
char			*get_time(time_t sec, char *buffer);
char			get_x_attr(const char *path, const char *filename);
char			get_x_attr_file(const char *filename);
char			get_x_attr_file(const char *filename);
void			get_attr(mode_t permission, char *str);
char			f_type(mode_t mode);
u_int			len_digital(long long value);
char			*get_attr_colour(mode_t permission, char *str);
void			sort_flag_f(char ***list, const u_int size,
					char ***color_files);
void			recursive_sort_flag_f(char ***list, const u_int size);
struct stat		get_stat(const char *path, const char *name);
void			respec_color_part_three(char *access, char **color,
						struct stat temp, int flag);
int				file_exist(const char *path);
int				ft_strcmp_simbol(const char *s1, const char *s2);
void			swap_stat_s(struct stat *a, struct stat *b);
void			swap_string(char **a, char **b);
unsigned int	print_dir(const char *path, u_int flags);
void			recursive(const char *path, u_int flags, int depth);
void			free_mas(char **str, int x);
char			*ft_temp(const char *path, const char *filename);
void			print_permission_denied(char *name);

#endif
