library(tidyverse)

random <- function(i)
{
  return(sum(runif(12)))
}

x <- tibble(x = sapply(1:1000000, random))

x.mean <- mean(x$x)
x.sd <- sd(x$x)

x.mean
x.sd

png(filename="density.png", res = 600, width = 4, height = 4, units = 'in')
x %>% ggplot(aes(x=x)) + geom_density(fill = 'grey', colour = 'grey', alpha = 0.5) + stat_function(fun = dnorm, args = list(mean = x.mean, sd = x.sd), size = 1, alpha = 0.5)

png(filename="qq_plot.png", res = 600, width = 4, height = 4, units = 'in')
x %>% ggplot(aes(sample=x)) + stat_qq(alpha = 0.2, size = 1, colour = 'darkgrey') + stat_qq_line()
dev.off()

ks.test(x = x$x, y = 'pnorm', alternative = 'two.sided')
