#include "philo_one.h"

long long current_timestamp()
{
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

static void * fn_philo (void * p_data)
{
  node *n;

  n = p_data;
  pthread_mutex_lock(n->lock_s);

  ft_putlnbr_fd(current_timestamp(), 1);
  write(1," ", 1);
  ft_putnbr_fd(n->value, 1);
  //  ft_putnbr_fd(*i, 1);
  write(1, " is thinking\n", 14);

  pthread_mutex_unlock(n->lock_s);
  return NULL;
}
 
int main (int ac, char **av)
{
  pthread_t thread_philo[3];
  pthread_mutex_t lock[3];
  pthread_mutex_t lock_std;
  int i;
  node n[3];
  void *t;
  
  (void)ac;
  (void)av;

  n[1].value = 1;
  n[1].next = &n[2];
  n[2].value = 2;
  n[2].next = &n[1];

  if (pthread_mutex_init(&lock_std, NULL) != 0)
     return EXIT_FAILURE;

  n[1].lock_s = &lock_std;
  n[2].lock_s = &lock_std;

  write(1, "Creation\n", 9);
  i = 1;
  while (i < 3)
  {
   t = &n[i];
   if (pthread_mutex_init(&lock[i], NULL) != 0)
     return EXIT_FAILURE;
   if(pthread_create(&thread_philo[i], NULL, fn_philo, t))
     return EXIT_FAILURE;
   i++;
  }
  i = 1;
  while (i < 3)
  {
    pthread_join (thread_philo[i], NULL);
    pthread_mutex_destroy(&lock[i]);
    i++;
  }
  pthread_mutex_destroy(&lock_std);
  return EXIT_SUCCESS;
}