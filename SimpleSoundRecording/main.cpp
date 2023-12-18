#include "music.h"

Disk disk;

namespace OpenSaveFile
{
	void OpenFile()
	{
		system("cls");
		std::cout << "Type file name with no extension:\n";
		std::string file;
		std::cin >> file;
		file += ".mds";
		std::ifstream fout{ file };
		if (!fout)
		{
			throw std::runtime_error("Trying open not exsisting file.");
		}
		disk.read(fout);
		fout.close();
	}

	void SaveFile()
	{
		system("cls");
		std::cout << "Type file name with no extension:\n";
		std::string file;
		std::cin >> file;
		file += ".mds";
		std::ofstream fout{ file };
		disk.print(fout);
		fout.close();
	}
}

namespace Reorder
{

	void ReorderMenu()
	{
		int a = 0;
		while (a != 6)
		{
			system("cls");
			std::cout << "Select:\n\t1) Random order\n\t2) Sort by lenght\n\t3) Sort by name\n\t4) Sort by style\n\t5) Sort by Author\n\t6) Exit\n";
			std::cin >> a;
			if (a == 1)
				disk.Shuffle();
			if (a == 2)
				disk.SortByLength();
			if (a == 3)
				disk.SortByName();
			if (a == 4)
				disk.SortByStyle();
			if (a == 5)
				disk.SortByAuthor();
		}
	}
}

namespace Select
{
	void SelectByStyleMenu()
	{
		std::string style;
		system("cls");
		std::cout << "Type style you want to select:\n";
		std::cin >> style;
		disk = disk.SelectByStyle(style);
	}

	void SelectByLengthMenu()
	{
		int min = -1, max = -1;
		system("cls");
		std::cout << "Print minimal and maximal length you want to select in seconds (to skip write -1 or less):\n";
		std::cin >> min >> max;
		disk = disk.SelectByLength(min > 0 ? min : 0, max > 0 ? max : 0);
	}

	void SelectMenu()
	{
		int a = 0;
		while (a != 6)
		{
			system("cls");
			std::cout << "Select:\n\t1) Select by style\n\t2) Select by time\n\t3) Select by style and time\n\t6) Exit\n";
			std::cin >> a;
			if (a == 1)
				SelectByStyleMenu();
			if (a == 2)
				SelectByLengthMenu();
			if (a == 3)
			{
				SelectByStyleMenu();
				SelectByLengthMenu();
			}
		}
	}
}

void MainMenu()
{
	int a = 0;
	while (a != 6)
	{
		system("cls");
		std::cout << "Select:\n\t1) Open file\n\t2) Save file\n\t3) Reorder\n\t4) Select\n\t5) Print\n\t6) Exit\n";
		std::cin >> a;
		if (a == 1)
			OpenSaveFile::OpenFile();
		if (a == 2)
			OpenSaveFile::SaveFile();
		if (a == 3)
			Reorder::ReorderMenu();
		if (a == 4)
			Select::SelectMenu();
		if (a == 5)
		{
			system("cls");
			disk.print(std::cout);
			system("pause");
		}
	}
	
}

int main()
{
	try
	{
		MainMenu();
	}
	catch (std::exception& ex)
	{
		std::cout << "Error during running program:\n\t";
		std::cout << ex.what();
		return -1;
	}
	return 0;
}