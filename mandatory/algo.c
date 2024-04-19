/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:42 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/04/18 14:38:44 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_stack(t_list *s)
{
	while (s)
	{
		printf("%d\n",s->data);
		s = s->next;
	}
}

static void	big_one(t_list **stack_a, t_list **stack_b)
{
	int	index;
	int	size ;

	while (*stack_b)
	{
		index = find_max(*stack_b);
		size = ft_lstsize(*stack_b) / 2;
		if (index == 0)
		{
			ft_push(stack_a, stack_b, 'a');
		}
		else if (index >= size)
		{
			ft_rrotate(stack_b, 'b');
		}
		else if (index < size)
		{
			ft_rotate(stack_b, 'b');
		}
	}
}

static void	sort(t_list **stack_a, t_list **stack_b, int start, int end)
{
	while (*stack_a)
	{
		if ((*stack_a)->index >= start && (*stack_a)->index <= end)
		{
			ft_push(stack_b, stack_a, 'b');
			start++;
			end++;
		}
		else if ((*stack_a)->index < start)
		{
			ft_push(stack_b, stack_a, 'b');
			ft_rotate(stack_b, 'b');
			start++;
			end++;
		}
		else
			ft_rotate(stack_a, 'a');
	}
}

static void	algo(t_list **stack_a,t_list **stack_b)
{
	int		len;

	len = ft_lstsize(*stack_a);
	if (len == 3)
		sort_three(stack_a);
	if (len == 2)
	{
		if ((*stack_a)->data > (*stack_a)->next->data)
			ft_swap(stack_a, 'a');
		return ;
	}
	else if (len == 5 || len == 4)
		sort_five(stack_a, stack_b);
	else if (len <= 100)
		sort(stack_a, stack_b, 0, 15);
	else if (len > 100 && len <= 500)
		sort(stack_a, stack_b, 0, 35);
	else
		sort(stack_a, stack_b, 0, 45);
	big_one(stack_a, stack_b);
	if (sorted(*stack_a) == true)
		ft_printf("done\n");
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	char	**str;
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	i = 1;
	if (ac > 1)
	{
		while (i < ac)
		{
			str = ft_split(av[i], ' ');
			j = 0;
			while (str[j])
			{
				ft_lstadd_back(&stack_a, ft_lstnew(ft_atoi(str[j])));
				free(str[j]);
				j++;
			}
			free(str);
			i++;
		}
		str = NULL;
	}
	set_index(&stack_a);
	algo(&stack_a, &stack_b);
	ft_lstfree(&stack_a);
	return (0); 
}
