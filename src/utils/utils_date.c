/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_date.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:39:02 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/02 05:01:43 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "utils.h"

int	is_leap(int year)
{
	if (year % 400 == 0)
		return (366);
	if (year % 100 == 0)
		return (365);
	if (year % 4 == 0)
		return (366);
	return (365);
}

// 28 -> 11100    | 00
// 29 -> 11101    | 01
// 30 -> 11110    | 10
// 31 -> 11111    | 11
// each hex digit represents day counts of 2 sequent months
// starting from january
//  11 00 11 10 11 10 11 11 10 11 10 11    | 0x00CEEFBB | NOT LEAP YEAR
//  11 01 11 10 11 10 11 11 10 11 10 11    | 0x00DEEFBB | LEAP YEAR
// month_days = {31,28,31,30,31,30,31,31,30,31,30,31}
//
// index 1 -> month january
// 1 means `shift 22 bits`
int	get_monthy(int val, int index)
{
	int	shift_count;

	shift_count = 24 - (2 * index);
	return (((val >> shift_count) & 0b11) + 28);
}

void	get_day(t_mydate *mydate)
{
	unsigned int	month_days;
	int				temp;

	month_days = 0x00CEEFBB;
	if (is_leap(mydate->year) == 366)
		month_days = 0x00DEEFBB;
	mydate->month = 1;
	while (mydate->month <= 12)
	{
		temp = get_monthy(month_days, mydate->month);
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

t_mydate	parse_date(struct timeval tv)
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
	t_mydate		mydate;
	struct timeval	tv;
	int				res;

	res = gettimeofday(&tv, NULL);
	if (res == -1)
		return ;
	mydate = parse_date(tv);
	utils_putstr(fd, "[ ");
	utils_put_unsigned_nb(fd, mydate.hour);
	utils_putchar(fd, ':');
	utils_put_unsigned_nb(fd, mydate.minute);
	utils_putchar(fd, ':');
	utils_put_unsigned_nb(fd, mydate.second);
	utils_putchar(fd, ':');
	utils_put_unsigned_nb(fd, mydate.usecond);
	utils_putstr(fd, " - ");
	utils_put_unsigned_nb(fd, mydate.day);
	utils_putchar(fd, '/');
	utils_put_unsigned_nb(fd, mydate.month);
	utils_putchar(fd, '/');
	utils_put_unsigned_nb(fd, mydate.year);
	utils_putstr(fd, " ] ");
}
