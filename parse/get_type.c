/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:59 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/31 01:32:18 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_line(t_vars *vars, int *index)
{
	if (!ft_strcmp(vars->line[0], "C"))
		parse_camera(vars->line, vars);
	else if (!ft_strcmp(vars->line[0], "A"))
		parse_ambient(vars->line, vars);
	else if (!ft_strcmp(vars->line[0], "L"))
		parse_light(vars->line, vars);
	else if (!ft_strcmp(vars->line[0], "sp"))
		parse_sphere(vars->line, vars, index);
	else if (!ft_strcmp(vars->line[0], "pl"))
		parse_plane(vars->line, vars, index);
	else if (!ft_strcmp(vars->line[0], "cy"))
		parse_cylender(vars->line, vars, index);
	else
		msg_exit_free("bad configuration file\n", 1, vars);
	free_tab(vars->line);
}

int	count_objs(char **line)
{
	int		i;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	while (line[i])
	{
		res = ft_split_two(line[i], "\t\n\v\f\r ");
		if (!ft_strcmp(res[0], "sp"))
			count++;
		if (!ft_strcmp(res[0], "cy"))
			count++;
		if (!ft_strcmp(res[0], "pl"))
			count++;
		free_tab(res);
		i++;
	}
	return (count);
}

void	get_content(t_vars *vars)
{
	int		i;
	int		index;
	int		flag;

	i = 0;
	flag = 0;
	index = 0;
	vars->obj_count = count_objs(vars->lines);
	vars->parse.obj = malloc(sizeof(t_object) * (vars->obj_count + 1));
	while (vars->lines[i])
	{
		vars->line = ft_split_two(vars->lines[i], "\t\n\v\f\r ");
		if (!ft_strcmp(vars->line[0], "C") || !ft_strcmp(vars->line[0], "L"))
			flag++;
		if (vars->line && vars->line[0])
			parse_line(vars, &index);
		i++;
	}
	if (flag != 2)
	{
		free(vars->lines);
		message_exit("parse file is not correct\n", 1);
	}
	free_tab(vars->lines);
}
