/**********************************************************
This is a simple PG_File demo that writes 2 ints to a file
Roger D. Vargas
**********************************************************/
#include <pgfilearchive.h>
#include <pgfile.h>
#include <pglog.h>
#include <string>

int main(int argc, char* argv[]) {
	PG_FileArchive *Arc;
	PG_File *wf;

	int v1=23444,v2=44566;

	// Create the FileArchive object
	Arc = new PG_FileArchive();

	// Set the base app dir as write dir
	Arc->SetWriteDir(PG_FileArchive::GetUserDir());

	// Now open a file for writing
	PG_LogMSG("creating writeable file ...");
	wf = Arc->OpenFile("pgtestfile", PG_FileArchive::WRITE);

	// Write a line of text (CR will be added)
	wf->putline("test");

	//Now write a couple of ints
	wf->write(&v1,sizeof(v1));
	wf->write(&v2,sizeof(v2));

	// close file
	delete wf;

	// Open created file for reading
	PG_LogMSG("checking file ...");
	wf = Arc->OpenFile("pgtestfile", PG_FileArchive::READ);

	// read and check the line of text
	std::string text = wf->getline();
	if(text != "test") {
		PG_LogERR("File corrupted (reading text failed)");
	}

	// read and check the ints
	int i=0;
	wf->read(&i, sizeof(i));
	if(i != v1) {
		PG_LogERR("File corrupted (reading int v1)");
	}

	wf->read(&i, sizeof(i));
	if(i != v2) {
		PG_LogERR("File corrupted (reading int v2)");
	}

	PG_LogMSG("check passed");

	// close file & archive
	delete wf;
	delete Arc;
}
