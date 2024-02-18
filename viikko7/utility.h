#pragma once

// Tää on turhinta paskaa mitä oon ikinä nähny
// Kirjan kirjottaja unohtuna c++ standardin
// jossa funktio/metodi palauttaa 0 jos se
// suoritetaan onnistuneesti, muuten joku muu arvo

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <time.h>
using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};

bool user_says_yes();
