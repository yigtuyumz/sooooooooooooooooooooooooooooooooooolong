/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_date.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:39:02 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/08 10:38:32 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "utils.h"
#include "../../printf/ft_fprintf.h"

static int	is_leap(int year)
{
	if (year % 400 == 0)
		return (366);
	if (year % 100 == 0)
		return (365);
	if (year % 4 == 0)
		return (366);
	return (365);
}

static void	get_day(t_mydate *mydate)
{
	unsigned int	month_days;
	int				temp;

	month_days = 0x00CEEFBB;
	if (is_leap(mydate->year) == 366)
		month_days = 0x00DEEFBB;
	mydate->month = 1;
	while (mydate->month <= 12)
	{
		temp = (((month_days >> (24 - (2 * mydate->month))) & 0b11) + 28);
		if (mydate->day >= temp)
		{
			mydate->day -= temp;
			mydate->month++;
		}
		else
		{
			mydate->day++;
			return ;
		}
	}
}

static t_mydate	parse_date(struct timeval tv)
{
	t_mydate	mydate;
	long		days;

	mydate.usecond = tv.tv_usec;
	days = tv.tv_sec / 86400;
	mydate.year = 1970;
	while (days >= is_leap(mydate.year))
		days -= is_leap(mydate.year++);
	mydate.day = days;
	get_day(&mydate);
	mydate.hour = (tv.tv_sec % 86400) / 3600;
	mydate.minute = ((tv.tv_sec % 86400) % 3600) / 60;
	mydate.second = (tv.tv_sec % 86400) % 60;
	return (mydate);
}

void	utils_putdate(int fd)
{
	struct timeval	tv;
	t_mydate		mydate;
	int				res;

	res = gettimeofday(&tv, NULL);
	if (res == -1)
	{
		(void) ft_fprintf(fd, "[01/01/1970 - 00:00:00:00]");
		return ;
	}
	mydate = parse_date(tv);
	(void) ft_fprintf(fd, "[ %d/%d/%d - %d:%d:%d%d ] ",
		mydate.day, mydate.month, mydate.year, mydate.hour,
		mydate.minute, mydate.second, mydate.usecond);
}
