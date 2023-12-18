#include "music.h"

int main()
{
	std::ifstream fin("disk.mds");
	Disk disk;
	disk.read(fin);
	
}