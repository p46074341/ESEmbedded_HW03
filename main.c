void reset_handler(void)
{	
	while (1)
	{
		function1(1, 2, 3, 4);
		caller1();
	}
		;
}

int function1(int a,int b, int c, int d)
{
	return a+b+c-d;
}

int caller1(void)
{
	return function1(4, 3, 2, 1);
}

