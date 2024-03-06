
unsigned int recurse_e1(unsigned int n)
{
	if (n == 0) { return 0; }
	if (n % 2 == 0) { return recurse_e1(n / 2); }
	return 1 + recurse_e1(n - 1);
}

unsigned int recurse_e2(unsigned int n)
{
	if (n < 2) { return n; }
	if (n % 2 == 0) { return recurse_e2(n / 2); }
	return recurse_e2((n + 1) / 2) + recurse_e2((n - 1) / 2);
}

unsigned int tower_of_hanoi_move_count(unsigned int height)
{
	if (height == 0) { return 0; }
	if (height == 1) { return 1; }
	return tower_of_hanoi_move_count(height - 1) * 2 + 1;
}
