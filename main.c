/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:10:35 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 16:16:08 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		handle_wo_arg(void)
{
	if (g_flags & FLAG_R)
		recursive(".", g_flags, 0);
	else
		print_dir(".", g_flags);
}

void			handle_one_arg(char **argv, u_int i)
{
	struct stat	temp;
	char		**files;

	files = (char**)malloc(sizeof(char*) * (2));
	if (!lstat(argv[i], &temp))
	{
		files[0] = argv[i];
		files[1] = respec_color_part_two(argv[i]);
		if (S_ISREG(temp.st_mode) || S_ISLNK(temp.st_mode))
			print_file(files, g_flags, 1);
		else if (S_ISDIR(temp.st_mode))
		{
			if (g_flags & FLAG_R)
				recursive(argv[i], g_flags, 0);
			else
				print_dir(argv[i], g_flags);
		}
	}
	else
		perror("ft_ls");
	free(files);
}

static u_int	g_c_files;
static u_int	g_c_dirs;

static void		put_list(char **argv, u_int i, char **files, char **dirs)
{
	struct stat	temp;

	if (!lstat(argv[i], &temp))
	{
		if (S_ISREG(temp.st_mode) || S_ISLNK(temp.st_mode))
		{
			files[g_c_files++] = argv[i];
			files[g_c_files++] = respec_color_part_two(argv[i]);
		}
		else if (S_ISDIR(temp.st_mode))
		{
			dirs[g_c_dirs++] = argv[i];
			dirs[g_c_dirs++] = respec_color_part_two(argv[i]);
		}
	}
	else
		perror("ft_ls");
}

static void		handle_many_arg(int argc, char **argv, u_int i)
{
	char		**files;
	char		**dirs;

	G_C_RESET;
	files = (char**)malloc(sizeof(char*) * (argc * 2));
	dirs = (char**)malloc(sizeof(char*) * (argc * 2));
	while (i < (u_int)argc)
		put_list(argv, i++, files, dirs);
	files[g_c_files] = NULL;
	dirs[g_c_dirs] = NULL;
	if (g_c_files != 0)
	{
		print_file(files, g_flags, g_c_files);
		(g_c_dirs) ? (ft_printf("\n")) : (0);
	}
	recursive_sort_alpha(&dirs, g_c_dirs);
	g_c_dirs = 0;
	while (dirs[g_c_dirs] != NULL)
	{
		(g_c_dirs) ? (ft_printf("\n")) : (0);
		ft_printf("%s:\n", dirs[g_c_dirs]);
		(g_flags & FLAG_R) ? (recursive(dirs[g_c_dirs], g_flags, 0)) :
		(print_dir(dirs[g_c_dirs], g_flags));
		g_c_dirs += 2;
	}
}

int				main(int argc, char **argv)
{
	u_int		i;

	g_flags = 0;
	i = 1;
	if (argc != 1)
		while ((i < (u_int)argc) && manage_flags(argv[i], &g_flags))
			i++;
	respec_flags();
	if (i == (u_int)argc || argc == 1)
		handle_wo_arg();
	else if (i == (u_int)(argc - 1))
		handle_one_arg(argv, i);
	else
		handle_many_arg(argc, argv, i);
	return (0);
}
