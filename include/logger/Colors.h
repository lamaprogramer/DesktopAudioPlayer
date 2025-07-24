#pragma once
#include <string>

namespace iamaprogrammer {

  class Colors {
  public:
    //Name            FG  BG
    static std::string Black;                         // 30  40
    static std::string Red;                           // 31  41
    static std::string Green;                         // 32  42
    static std::string Yellow;                        // 33  43
    static std::string Blue;                          // 34  44
    static std::string Magenta;                       // 35  45
    static std::string Cyan;                          // 36  46
    static std::string White;                         // 37  47
    static std::string BrightBlack;                   // 90  100
    static std::string BrightRed;                     // 91  101
    static std::string BrightGreen;                   // 92  102
    static std::string BrightYellow;                  // 93  103
    static std::string BrightBlue;                    // 94  104
    static std::string BrightMagenta;                 // 95  105
    static std::string BrightCyan;                    // 96  106
    static std::string BrightWhite;                   // 97  107

    static std::string Terminate;
  };
}