/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:02:35 by chughes           #+#    #+#             */
/*   Updated: 2022/09/28 12:55:56 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Adds node to back of data->vars
static void	t_var_add(t_var *new_node)
{
	t_data	*data;
	t_var	*temp;

	data = get_data();
	temp = data->vars;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return ;	
}

// Adds new node to list or modifies existing node with name
void	t_var_new_node(char *name, char *val)
{
	t_var	*node;

	if (t_var_search(name))
	{
		node = t_var_search(name);
		xfree(node->val);
		node->val = val;
		return ;
	}
	node = (t_var *)ft_calloc(1, sizeof(t_var));
	node->name = name;
	node->val = val;
	t_var_add(node);
	return ;
}

// Returns pointer to node with name or NULL if no match
t_var	*t_var_search(char *name)
{
	t_data	*data;
	t_var	*node;
	
	data = get_data();
	node = data->vars;
	while (ft_strncmp(node->name, name, ft_strlen(name)) != 0 && node)
		node = node->next;
	return (node);
}

//free the nodes
void	t_var_del_all(void)
{
	t_data	*data;
	t_var	*head;
	t_var	*temp;

	data = get_data();
	head = data->vars;
	temp = head;
	while (head)
	{
		xfree(temp->name);
		xfree(temp->val);
		head = temp->next;
		xfree(temp);
	}
}
