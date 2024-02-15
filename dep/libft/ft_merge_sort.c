/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:34:42 by mde-clee          #+#    #+#             */
/*   Updated: 2023/07/28 20:08:45 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ms_allocate(int **left_arr, int **right_arr, \
		int *arr, int index_data[5])
{
	if (index_data[3])
	{
		*left_arr = malloc(index_data[3] * sizeof(int));
		if (!(*left_arr))
			return (0);
	}
	else
		*left_arr = 0;
	if (index_data[4])
	{
		*right_arr = malloc(index_data[4] * sizeof(int));
		if (!(*right_arr))
		{
			free(*left_arr);
			return (0);
		}
	}
	else
		*right_arr = 0;
	ft_memcpy(*left_arr, arr + index_data[0], index_data[3] * sizeof(int));
	ft_memcpy(*right_arr, arr + index_data[1] + 1, index_data[4] * sizeof(int));
	return (1);
}

static int	ms_merge(int *arr, int index_data[5])
{
	int	*left_arr;
	int	*right_arr;
	int	i;
	int	j;

	if (!(ms_allocate(&left_arr, &right_arr, arr, index_data)))
		return (0);
	i = 0;
	j = 0;
	arr += index_data[0];
	while (i < index_data[3] && j < index_data[4])
	{
		if (left_arr[i] <= right_arr[j])
			*arr++ = left_arr[i++];
		else
			*arr++ = right_arr[j++];
	}
	while (i < index_data[3])
		*arr++ = left_arr[i++];
	while (j < index_data[4])
		*arr++ = right_arr[j++];
	free(left_arr);
	free(right_arr);
	return (1);
}

static int	ms_divide(int *arr, int first_index, int last_index)
{
	int	index_data[5];
	int	middle_index;
	int	left_size;
	int	right_size;

	if (first_index >= last_index)
		return (1);
	else
	{
		middle_index = first_index + (last_index - first_index) / 2;
		ms_divide(arr, first_index, middle_index);
		ms_divide(arr, middle_index + 1, last_index);
		left_size = middle_index - first_index + 1;
		right_size = last_index - middle_index;
		index_data[0] = first_index;
		index_data[1] = middle_index;
		index_data[2] = last_index;
		index_data[3] = left_size;
		index_data[4] = right_size;
		if (!(ms_merge(arr, index_data)))
			return (0);
	}
	return (1);
}

int	ft_merge_sort(int *arr, int size)
{
	if (!(ms_divide(arr, 0, size - 1)))
		return (0);
	return (1);
}
