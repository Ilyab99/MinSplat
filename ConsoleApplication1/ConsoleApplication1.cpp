# include <FL/Fl.H>
# include <FL/Fl_Window.H>
# include <FL/Fl_Button.H>
#include <iostream>
#include <soloud.h>
#include <soloud_audiosource.h>
#include <soloud_wav.h>
#include <soloud_speech.h>
#include <soloud_thread.h>
#define WITH_WINMM
#include <fstream>
#include <string>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Box.H>

#include <FL/Fl_File_Browser.H>
//Fl_Box box1{ 10, 220, 480, 25, "(none)" };
SoLoud::Soloud soloud;
SoLoud::Speech speech;
SoLoud::Wav sample;
using namespace std;
#pragma comment(linker,"/ENTRY:mainCRTStartup")


void whenPushed(Fl_Widget*, void*)
{


//	sample.load("2.mp3");
	soloud.playBackground(sample);
	int handle = soloud.play(sample);
	soloud.setVolume(handle, 0.5f);
	printf("Ouch!\n");
}

void whenPushed2(Fl_Widget*, void*)
{
	soloud.setPauseAll(1);

}

void whenPushed3(Fl_Widget*, void*)
{
	soloud.setPauseAll(0);
}

int main(int argc, char** argv){
	soloud.init();
	std::cout << Fl::event_text();
	Fl_Window* w = new Fl_Window(180, 260,200,400,"MinSplat");
	Fl_Button* button = new Fl_Button(10, 20, 90, 20, "Play Song");
	Fl_Button* button2 = new Fl_Button(10, 40, 90, 20, "Pause");
	Fl_Button* button3 = new Fl_Button(10, 60, 90, 20, "Resume");
	Fl_File_Browser* file_browser = new Fl_File_Browser { 10, 120, 200, 200 };
	Fl_Box* box1 = new Fl_Box{ 100, 80, 90, 20, ""};
	file_browser->load("folder");
	w->resizable(w);
	//
	file_browser->type(FL_HOLD_BROWSER);
	file_browser->filetype(Fl_File_Browser::FILES);
	file_browser->filter("*.*");
	file_browser->callback([](Fl_Widget* sender, void* data) {
		auto file_browser = dynamic_cast<Fl_File_Browser*>(sender);
		auto box = reinterpret_cast<Fl_Box*>(data);
		std::cout << file_browser->text(file_browser->value());
		//box->copy_label(file_browser->text(file_browser->value()));}, &box1);
		sample.load(file_browser->text(file_browser->value()));
		//soloud.playBackground(sample);
	//	int handle = soloud.play(sample);
	//	soloud.setVolume(handle, 0.5f);
		});

	button->callback(whenPushed);
	button2->callback(whenPushed2);
	button3->callback(whenPushed3);
	w->end();
	w->show(argc, argv);
	return Fl::run();
	delete &soloud;
	
}
