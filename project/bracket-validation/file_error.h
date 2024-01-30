class File_error {
public:
	File_error(
		size_t aRow, 
		size_t aCol, 
		char aExpected_sym,
		char aFound_sym
	);
public:
	size_t row;
	size_t col;
	char expected_sym;
	char found_sym;
};

File_error::File_error(
	size_t aRow,
	size_t aCol,
	char aExpected_sym,
	char aFound_sym)
{
	row = aRow;
	col = aCol;
	expected_sym = aExpected_sym;
	found_sym = aFound_sym;
}
