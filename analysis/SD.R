standard_deviation <- function(file_name)
{
  data = read.table(file_name, header = T)
  x = data['minimum'] 
  sd(x);
}