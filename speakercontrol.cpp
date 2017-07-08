#include "tpa2016/Adafruit_TPA2016.cpp"
#include <iostream>
#include <boost/program_options.hpp>
#include <curses.h>

namespace po = boost::program_options;

Adafruit_TPA2016 audioamp = Adafruit_TPA2016();

int x = 2;
int y = 2;
int gain = -30;
bool muted = false;

const int max_gain = 30;
const int min_gain = -28;
const int increment = 1;

const char key_plus = 'y';
const char key_minus = 'a';
const char key_mute = 'x';
const char key_unmute = 's';


int main(int argc, char* argv[])
{
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("getGain,g", "get Gain")
    ("setGain,s", po::value<int>(), "set Gain")
    ("mute", po::value<bool>()->default_value(true), "set mute on/off")
    ("interactive,i", "interactive control");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if(vm.count("help")) {
    std::cout << "not sure yet" << std::endl;
  }

  audioamp.begin();
  if(vm.count("getGain")) {
    std::cout << (unsigned)audioamp.getGain() << std::endl;
  }
  if(vm.count("setGain")) {
    audioamp.setGain(vm["setGain"].as<int>());
  }
  if(vm.count("mute")) {
    audioamp.enableChannel(!vm["mute"].as<bool>(), !vm["mute"].as<bool>());
  }
  if(vm.count("interactive")) {
    gain = audioamp.getGain();
    try {
      int c = 0;
      bool exit = false;
      initscr();
      noecho();
      cbreak();
      timeout(500);
      while(c != 'q' && !exit) {
        c = getch();

      //std::cout << "pressed: " << c << " ("<< (int)c << ") ";
      //if(c==EOF)
      //  std::cout << "EOF";
      //std::cout << std::endl;
      //if((int)c==255) continue;

        switch(c) {
          case key_plus:
            audioamp.setGain(gain+increment);
            break;
          case key_minus:
            audioamp.setGain(gain-increment);
            break;
          case key_mute:
            muted=true;
            audioamp.enableChannel(false,false);
            break;
          case key_unmute:
            muted=false;
            audioamp.enableChannel(true,true);
            break;
        }

        clear();
        move(1,1);
        gain = audioamp.getGain();
        printw("%d",gain);

        move(x,y-1);
        printw("[");

        move(x,y+max_gain-min_gain+1);
        printw("]");

        move(x,y+gain-min_gain);
        if(muted)
          printw("X");
        else
          printw("|");
        //printw("pressed: %c (%d)",c,(int)c);
        usleep(1000);
        if(c=='\n' || c=='\r') exit=true;
      }
    } catch(...) {}
    nocbreak();
    echo();
    endwin();
  }
  return 0;
}
