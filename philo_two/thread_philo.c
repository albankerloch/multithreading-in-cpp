#include "philo_one.h"
void		ft_chg_str(node *n, char *str, unsigned int t, unsigned int j)
{
	unsigned int i;
	
	i = 0;
	while (i < j)
	{
		n->str[i + t] = str[i];
		i++;
	}
	n->str[i + t ] = '\n';
	n->str[i + t + 1] = '\0';
}

void		ft_message(node *n, char *str, long long tm, unsigned int j)
{
	unsigned int t;

	pthread_mutex_lock(n->lock_s);
	//ft_putlnbr_fd(tm, 1);
	ft_putlnbr_str(tm, n);
	n->str[13] = ' ';
	ft_putnbr_str(n->value, n);
	//ft_putnbr_fd(n->value, 1);
	t = ft_strlen(n->str);
	//ft_putnbr_fd(t, 1);
	n->str[t] = ' ';
	ft_chg_str(n, str, t, j);
	write(1, n->str, ft_strlen(n->str));
	//n->str[0] = '\0';
	//write(1, str, ft_strlen(str));
	pthread_mutex_unlock(n->lock_s);
}

static void	ft_activity(node *n)
{
	pthread_mutex_lock(&(n->lock));
	n->fork_lock = 1;
	pthread_mutex_lock(&(n->next->lock));
	n->next->fork_lock = 1;
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	n->start = current_timestamp();
	n->count_eat = n->count_eat + 1;
	ft_message(n, " is eating\n", n->start, 10);
	usleep(n->tt_eat * 1000);
	n->next->fork_lock = 0;
	pthread_mutex_unlock(&(n->next->lock));
	n->fork_lock = 0;
	pthread_mutex_unlock(&(n->lock));
	if (n->count_eat == n->nb_eat)
		while (1)
		{
			usleep(5000 * 1000);
		}
	ft_message(n, " is sleeping\n", current_timestamp(), 12);
	usleep(n->tt_sleep * 1000);
	ft_message(n, " is thinking\n", current_timestamp(), 12);
}

void		*fn_philo(void *p_data)
{
	node *n;

	n = p_data;
	n->start = current_timestamp();
	if (pthread_create(&(n->monitor_die), NULL, fn_monitor, p_data))
		return (0);
	pthread_detach(n->monitor_die);
	ft_message(n, " is thinking\n", n->start, 12);
	while (1)
	{
		while (!(n->fork_lock == 0 && n->next->fork_lock == 0))
		{
			usleep(10);
		}
		ft_activity(n);
	}
	return (0);
}
