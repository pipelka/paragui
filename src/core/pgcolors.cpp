/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Alexander Pipelka
    pipelka@teleweb.at

    Last Update:      $Author: braindead $
    Update Date:      $Date: 2004/06/26 08:03:47 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgcolors.cpp,v $
    CVS/RCS Revision: $Revision: 1.1.6.1.2.1 $
    Status:           $State: Exp $

    Autogenerated from rgb.txt on Sun Sep 30 00:18:09 2001
*/

#define USE_COLOR_CONSTANTS
#include "pgcolors.h"

PG_Colors::colormap PG_Colors::colors;
bool PG_Colors::initialized = false;

void PG_Colors::InitColors() {

	colors["gray80"] = gray80;
	colors["grey80"] = grey80;
	colors["gray24"] = gray24;
	colors["grey24"] = grey24;
	colors["LightYellow4"] = LightYellow4;
	colors["lavender_blush"] = lavender_blush;
	colors["LavenderBlush"] = LavenderBlush;
	colors["LavenderBlush1"] = LavenderBlush1;
	colors["lime_green"] = lime_green;
	colors["LimeGreen"] = LimeGreen;
	colors["gray88"] = gray88;
	colors["grey88"] = grey88;
	colors["gray15"] = gray15;
	colors["grey15"] = grey15;
	colors["HotPink1"] = HotPink1;
	colors["yellow"] = yellow;
	colors["RoyalBlue1"] = RoyalBlue1;
	colors["gray23"] = gray23;
	colors["grey23"] = grey23;
	colors["DarkOrchid4"] = DarkOrchid4;
	colors["PaleVioletRed2"] = PaleVioletRed2;
	colors["pale_violet_red"] = pale_violet_red;
	colors["PaleVioletRed"] = PaleVioletRed;
	colors["LightCyan2"] = LightCyan2;
	colors["thistle4"] = thistle4;
	colors["turquoise2"] = turquoise2;
	colors["dark_violet"] = dark_violet;
	colors["DarkViolet"] = DarkViolet;
	colors["LightSkyBlue3"] = LightSkyBlue3;
	colors["LightBlue3"] = LightBlue3;
	colors["SpringGreen2"] = SpringGreen2;
	colors["RoyalBlue2"] = RoyalBlue2;
	colors["sea_green"] = sea_green;
	colors["SeaGreen"] = SeaGreen;
	colors["gainsboro"] = gainsboro;
	colors["pale_turquoise"] = pale_turquoise;
	colors["PaleTurquoise"] = PaleTurquoise;
	colors["seashell2"] = seashell2;
	colors["dark_red"] = dark_red;
	colors["DarkRed"] = DarkRed;
	colors["PeachPuff3"] = PeachPuff3;
	colors["peru"] = peru;
	colors["SteelBlue2"] = SteelBlue2;
	colors["orchid1"] = orchid1;
	colors["seashell3"] = seashell3;
	colors["gray89"] = gray89;
	colors["grey89"] = grey89;
	colors["navajo_white"] = navajo_white;
	colors["NavajoWhite"] = NavajoWhite;
	colors["NavajoWhite1"] = NavajoWhite1;
	colors["gray97"] = gray97;
	colors["grey97"] = grey97;
	colors["LightYellow3"] = LightYellow3;
	colors["lavender"] = lavender;
	colors["LavenderBlush3"] = LavenderBlush3;
	colors["gray32"] = gray32;
	colors["grey32"] = grey32;
	colors["HotPink2"] = HotPink2;
	colors["SlateBlue4"] = SlateBlue4;
	colors["gray40"] = gray40;
	colors["grey40"] = grey40;
	colors["DarkOrchid3"] = DarkOrchid3;
	colors["PaleVioletRed1"] = PaleVioletRed1;
	colors["dark_slate_blue"] = dark_slate_blue;
	colors["DarkSlateBlue"] = DarkSlateBlue;
	colors["gray55"] = gray55;
	colors["grey55"] = grey55;
	colors["gray48"] = gray48;
	colors["grey48"] = grey48;
	colors["thistle3"] = thistle3;
	colors["light_salmon"] = light_salmon;
	colors["LightSalmon"] = LightSalmon;
	colors["LightSalmon1"] = LightSalmon1;
	colors["LightSkyBlue2"] = LightSkyBlue2;
	colors["turquoise1"] = turquoise1;
	colors["gray63"] = gray63;
	colors["grey63"] = grey63;
	colors["gray7"] = gray7;
	colors["grey7"] = grey7;
	colors["aquamarine2"] = aquamarine2;
	colors["LavenderBlush4"] = LavenderBlush4;
	colors["LightBlue2"] = LightBlue2;
	colors["gray71"] = gray71;
	colors["grey71"] = grey71;
	colors["salmon1"] = salmon1;
	colors["gray79"] = gray79;
	colors["grey79"] = grey79;
	colors["gray6"] = gray6;
	colors["grey6"] = grey6;
	colors["green_yellow"] = green_yellow;
	colors["GreenYellow"] = GreenYellow;
	colors["gray87"] = gray87;
	colors["grey87"] = grey87;
	colors["gray14"] = gray14;
	colors["grey14"] = grey14;
	colors["light_yellow"] = light_yellow;
	colors["LightYellow"] = LightYellow;
	colors["LightYellow1"] = LightYellow1;
	colors["PeachPuff2"] = PeachPuff2;
	colors["gray22"] = gray22;
	colors["grey22"] = grey22;
	colors["SteelBlue1"] = SteelBlue1;
	colors["LightBlue4"] = LightBlue4;
	colors["sienna"] = sienna;
	colors["light_pink"] = light_pink;
	colors["LightPink"] = LightPink;
	colors["magenta4"] = magenta4;
	colors["dark_magenta"] = dark_magenta;
	colors["DarkMagenta"] = DarkMagenta;
	colors["dark_cyan"] = dark_cyan;
	colors["DarkCyan"] = DarkCyan;
	colors["dark_orchid"] = dark_orchid;
	colors["DarkOrchid"] = DarkOrchid;
	colors["thistle1"] = thistle1;
	colors["PaleGreen3"] = PaleGreen3;
	colors["medium_orchid"] = medium_orchid;
	colors["MediumOrchid"] = MediumOrchid;
	colors["dark_sea_green"] = dark_sea_green;
	colors["DarkSeaGreen"] = DarkSeaGreen;
	colors["LavenderBlush2"] = LavenderBlush2;
	colors["powder_blue"] = powder_blue;
	colors["PowderBlue"] = PowderBlue;
	colors["LightYellow2"] = LightYellow2;
	colors["snow4"] = snow4;
	colors["medium_spring_green"] = medium_spring_green;
	colors["MediumSpringGreen"] = MediumSpringGreen;
	colors["DeepPink3"] = DeepPink3;
	colors["light_goldenrod_yellow"] = light_goldenrod_yellow;
	colors["LightGoldenrodYellow"] = LightGoldenrodYellow;
	colors["slate_gray"] = slate_gray;
	colors["SlateGray"] = SlateGray;
	colors["slate_grey"] = slate_grey;
	colors["SlateGrey"] = SlateGrey;
	colors["SlateBlue3"] = SlateBlue3;
	colors["dark_green"] = dark_green;
	colors["DarkGreen"] = DarkGreen;
	colors["DarkOrchid2"] = DarkOrchid2;
	colors["LightPink4"] = LightPink4;
	colors["thistle2"] = thistle2;
	colors["CadetBlue4"] = CadetBlue4;
	colors["salmon"] = salmon;
	colors["LightSkyBlue1"] = LightSkyBlue1;
	colors["LightBlue1"] = LightBlue1;
	colors["wheat4"] = wheat4;
	colors["peach_puff"] = peach_puff;
	colors["PeachPuff"] = PeachPuff;
	colors["PeachPuff1"] = PeachPuff1;
	colors["dark_salmon"] = dark_salmon;
	colors["DarkSalmon"] = DarkSalmon;
	colors["gray96"] = gray96;
	colors["grey96"] = grey96;
	colors["alice_blue"] = alice_blue;
	colors["AliceBlue"] = AliceBlue;
	colors["gray31"] = gray31;
	colors["grey31"] = grey31;
	colors["gray95"] = gray95;
	colors["grey95"] = grey95;
	colors["gray39"] = gray39;
	colors["grey39"] = grey39;
	colors["cornflower_blue"] = cornflower_blue;
	colors["CornflowerBlue"] = CornflowerBlue;
	colors["pink"] = pink;
	colors["DodgerBlue4"] = DodgerBlue4;
	colors["gray54"] = gray54;
	colors["grey54"] = grey54;
	colors["gray47"] = gray47;
	colors["grey47"] = grey47;
	colors["magenta3"] = magenta3;
	colors["deep_sky_blue"] = deep_sky_blue;
	colors["DeepSkyBlue"] = DeepSkyBlue;
	colors["DeepSkyBlue1"] = DeepSkyBlue1;
	colors["gray62"] = gray62;
	colors["grey62"] = grey62;
	colors["MediumOrchid4"] = MediumOrchid4;
	colors["deep_pink"] = deep_pink;
	colors["DeepPink"] = DeepPink;
	colors["DeepPink1"] = DeepPink1;
	colors["DarkSlateGray4"] = DarkSlateGray4;
	colors["gray70"] = gray70;
	colors["grey70"] = grey70;
	colors["MediumPurple4"] = MediumPurple4;
	colors["PaleGreen1"] = PaleGreen1;
	colors["orchid"] = orchid;
	colors["dark_olive_green"] = dark_olive_green;
	colors["DarkOliveGreen"] = DarkOliveGreen;
	colors["gray78"] = gray78;
	colors["grey78"] = grey78;
	colors["gray5"] = gray5;
	colors["grey5"] = grey5;
	colors["snow3"] = snow3;
	colors["chartreuse"] = chartreuse;
	colors["gray86"] = gray86;
	colors["grey86"] = grey86;
	colors["gray13"] = gray13;
	colors["grey13"] = grey13;
	colors["DeepPink2"] = DeepPink2;
	colors["SlateBlue2"] = SlateBlue2;
	colors["aquamarine"] = aquamarine;
	colors["aquamarine1"] = aquamarine1;
	colors["bisque4"] = bisque4;
	colors["gray77"] = gray77;
	colors["grey77"] = grey77;
	colors["gray21"] = gray21;
	colors["grey21"] = grey21;
	colors["DarkOrchid1"] = DarkOrchid1;
	colors["LightPink3"] = LightPink3;
	colors["saddle_brown"] = saddle_brown;
	colors["SaddleBrown"] = SaddleBrown;
	colors["dark_blue"] = dark_blue;
	colors["DarkBlue"] = DarkBlue;
	colors["gray85"] = gray85;
	colors["grey85"] = grey85;
	colors["SkyBlue4"] = SkyBlue4;
	colors["CadetBlue3"] = CadetBlue3;
	colors["LightSteelBlue4"] = LightSteelBlue4;
	colors["indian_red"] = indian_red;
	colors["IndianRed"] = IndianRed;
	colors["wheat3"] = wheat3;
	colors["white_smoke"] = white_smoke;
	colors["WhiteSmoke"] = WhiteSmoke;
	colors["bisque"] = bisque;
	colors["bisque1"] = bisque1;
	colors["brown"] = brown;
	colors["MediumOrchid1"] = MediumOrchid1;
	colors["light_blue"] = light_blue;
	colors["LightBlue"] = LightBlue;
	colors["LightGoldenrod3"] = LightGoldenrod3;
	colors["azure"] = azure;
	colors["azure1"] = azure1;
	colors["honeydew4"] = honeydew4;
	colors["medium_aquamarine"] = medium_aquamarine;
	colors["MediumAquamarine"] = MediumAquamarine;
	colors["aquamarine3"] = aquamarine3;
	colors["pale_goldenrod"] = pale_goldenrod;
	colors["PaleGoldenrod"] = PaleGoldenrod;
	colors["DodgerBlue3"] = DodgerBlue3;
	colors["magenta2"] = magenta2;
	colors["MediumOrchid3"] = MediumOrchid3;
	colors["LightPink1"] = LightPink1;
	colors["DarkSlateGray3"] = DarkSlateGray3;
	colors["PaleGreen2"] = PaleGreen2;
	colors["light_green"] = light_green;
	colors["LightGreen"] = LightGreen;
	colors["MediumPurple3"] = MediumPurple3;
	colors["VioletRed3"] = VioletRed3;
	colors["snow"] = snow;
	colors["snow1"] = snow1;
	colors["plum"] = plum;
	colors["snow2"] = snow2;
	colors["green"] = green;
	colors["gray30"] = gray30;
	colors["grey30"] = grey30;
	colors["bisque3"] = bisque3;
	colors["SlateBlue1"] = SlateBlue1;
	colors["gray94"] = gray94;
	colors["grey94"] = grey94;
	colors["gray38"] = gray38;
	colors["grey38"] = grey38;
	colors["LightPink2"] = LightPink2;
	colors["gray53"] = gray53;
	colors["grey53"] = grey53;
	colors["gray46"] = gray46;
	colors["grey46"] = grey46;
	colors["CadetBlue2"] = CadetBlue2;
	colors["dodger_blue"] = dodger_blue;
	colors["DodgerBlue"] = DodgerBlue;
	colors["DodgerBlue1"] = DodgerBlue1;
	colors["SkyBlue3"] = SkyBlue3;
	colors["gray61"] = gray61;
	colors["grey61"] = grey61;
	colors["LightSteelBlue3"] = LightSteelBlue3;
	colors["hot_pink"] = hot_pink;
	colors["HotPink"] = HotPink;
	colors["gray69"] = gray69;
	colors["grey69"] = grey69;
	colors["wheat1"] = wheat1;
	colors["firebrick"] = firebrick;
	colors["gray60"] = gray60;
	colors["grey60"] = grey60;
	colors["gray4"] = gray4;
	colors["grey4"] = grey4;
	colors["plum4"] = plum4;
	colors["honeydew3"] = honeydew3;
	colors["light_steel_blue"] = light_steel_blue;
	colors["LightSteelBlue"] = LightSteelBlue;
	colors["LightGoldenrod1"] = LightGoldenrod1;
	colors["gray68"] = gray68;
	colors["grey68"] = grey68;
	colors["gray12"] = gray12;
	colors["grey12"] = grey12;
	colors["khaki"] = khaki;
	colors["dim_gray"] = dim_gray;
	colors["DimGray"] = DimGray;
	colors["dim_grey"] = dim_grey;
	colors["DimGrey"] = DimGrey;
	colors["gray76"] = gray76;
	colors["grey76"] = grey76;
	colors["gray20"] = gray20;
	colors["grey20"] = grey20;
	colors["navy"] = navy;
	colors["navy_blue"] = navy_blue;
	colors["NavyBlue"] = NavyBlue;
	colors["DodgerBlue2"] = DodgerBlue2;
	colors["gray84"] = gray84;
	colors["grey84"] = grey84;
	colors["dark_khaki"] = dark_khaki;
	colors["DarkKhaki"] = DarkKhaki;
	colors["MediumOrchid2"] = MediumOrchid2;
	colors["pink4"] = pink4;
	colors["rosy_brown"] = rosy_brown;
	colors["RosyBrown"] = RosyBrown;
	colors["DarkSlateGray2"] = DarkSlateGray2;
	colors["gray51"] = gray51;
	colors["grey51"] = grey51;
	colors["MediumPurple2"] = MediumPurple2;
	colors["VioletRed1"] = VioletRed1;
	colors["SeaGreen3"] = SeaGreen3;
	colors["violet"] = violet;
	colors["blanched_almond"] = blanched_almond;
	colors["BlanchedAlmond"] = BlanchedAlmond;
	colors["mint_cream"] = mint_cream;
	colors["MintCream"] = MintCream;
	colors["gray50"] = gray50;
	colors["grey50"] = grey50;
	colors["azure4"] = azure4;
	colors["cadet_blue"] = cadet_blue;
	colors["CadetBlue"] = CadetBlue;
	colors["bisque2"] = bisque2;
	colors["blue"] = blue;
	colors["blue1"] = blue1;
	colors["SkyBlue2"] = SkyBlue2;
	colors["CadetBlue1"] = CadetBlue1;
	colors["light_cyan"] = light_cyan;
	colors["LightCyan"] = LightCyan;
	colors["LightCyan1"] = LightCyan1;
	colors["red"] = red;
	colors["LightSteelBlue2"] = LightSteelBlue2;
	colors["wheat2"] = wheat2;
	colors["chocolate"] = chocolate;
	colors["plum3"] = plum3;
	colors["LightGoldenrod2"] = LightGoldenrod2;
	colors["thistle"] = thistle;
	colors["lawn_green"] = lawn_green;
	colors["LawnGreen"] = LawnGreen;
	colors["honeydew2"] = honeydew2;
	colors["gray29"] = gray29;
	colors["grey29"] = grey29;
	colors["antique_white"] = antique_white;
	colors["AntiqueWhite"] = AntiqueWhite;
	colors["gray93"] = gray93;
	colors["grey93"] = grey93;
	colors["gray37"] = gray37;
	colors["grey37"] = grey37;
	colors["LemonChiffon4"] = LemonChiffon4;
	colors["ivory3"] = ivory3;
	colors["spring_green"] = spring_green;
	colors["SpringGreen"] = SpringGreen;
	colors["SpringGreen1"] = SpringGreen1;
	colors["dark_grey"] = dark_grey;
	colors["DarkGrey"] = DarkGrey;
	colors["dark_gray"] = dark_gray;
	colors["DarkGray"] = DarkGray;
	colors["gray52"] = gray52;
	colors["grey52"] = grey52;
	colors["gray45"] = gray45;
	colors["grey45"] = grey45;
	colors["pink3"] = pink3;
	colors["DarkSlateGray1"] = DarkSlateGray1;
	colors["MediumPurple1"] = MediumPurple1;
	colors["magenta"] = magenta;
	colors["magenta1"] = magenta1;
	colors["VioletRed2"] = VioletRed2;
//#ifdef __BORLANDC__
//#else
//#if PG_VERSIONNUM(__GNUC__, __GNUC_MINOR__, 0) < PG_VERSIONNUM(3, 1, 0)
//	colors["tan"] = tan;
//#endif
//#endif
	colors["SeaGreen2"] = SeaGreen2;
	colors["gray59"] = gray59;
	colors["grey59"] = grey59;
	colors["gray3"] = gray3;
	colors["grey3"] = grey3;
	colors["steel_blue"] = steel_blue;
	colors["SteelBlue"] = SteelBlue;
	colors["honeydew"] = honeydew;
	colors["honeydew1"] = honeydew1;
	colors["gray67"] = gray67;
	colors["grey67"] = grey67;
	colors["gray11"] = gray11;
	colors["grey11"] = grey11;
	colors["burlywood1"] = burlywood1;
	colors["azure3"] = azure3;
	colors["gray75"] = gray75;
	colors["grey75"] = grey75;
	colors["gray19"] = gray19;
	colors["grey19"] = grey19;
	colors["khaki2"] = khaki2;
	colors["blue4"] = blue4;
	colors["light_sky_blue"] = light_sky_blue;
	colors["LightSkyBlue"] = LightSkyBlue;
	colors["midnight_blue"] = midnight_blue;
	colors["MidnightBlue"] = MidnightBlue;
	colors["gray83"] = gray83;
	colors["grey83"] = grey83;
	colors["PaleTurquoise4"] = PaleTurquoise4;
	colors["cyan"] = cyan;
	colors["cyan1"] = cyan1;
	colors["SkyBlue1"] = SkyBlue1;
	colors["olive_drab"] = olive_drab;
	colors["OliveDrab"] = OliveDrab;
	colors["LightSteelBlue1"] = LightSteelBlue1;
	colors["dark_goldenrod"] = dark_goldenrod;
	colors["DarkGoldenrod"] = DarkGoldenrod;
	colors["burlywood3"] = burlywood3;
	colors["papaya_whip"] = papaya_whip;
	colors["PapayaWhip"] = PapayaWhip;
	colors["plum2"] = plum2;
	colors["khaki3"] = khaki3;
	colors["gray49"] = gray49;
	colors["grey49"] = grey49;
	colors["AntiqueWhite4"] = AntiqueWhite4;
	colors["linen"] = linen;
	colors["DarkSeaGreen4"] = DarkSeaGreen4;
	colors["ivory2"] = ivory2;
	colors["LemonChiffon3"] = LemonChiffon3;
	colors["RosyBrown4"] = RosyBrown4;
	colors["royal_blue"] = royal_blue;
	colors["RoyalBlue"] = RoyalBlue;
	colors["pink2"] = pink2;
	colors["cyan4"] = cyan4;
	colors["orange_red"] = orange_red;
	colors["OrangeRed"] = OrangeRed;
	colors["purple4"] = purple4;
	colors["maroon3"] = maroon3;
	colors["SeaGreen1"] = SeaGreen1;
	colors["medium_blue"] = medium_blue;
	colors["MediumBlue"] = MediumBlue;
	colors["blue3"] = blue3;
	colors["seashell"] = seashell;
	colors["seashell1"] = seashell1;
	colors["light_coral"] = light_coral;
	colors["LightCoral"] = LightCoral;
	colors["ivory4"] = ivory4;
	colors["medium_purple"] = medium_purple;
	colors["MediumPurple"] = MediumPurple;
	colors["gray28"] = gray28;
	colors["grey28"] = grey28;
	colors["burlywood2"] = burlywood2;
	colors["azure2"] = azure2;
	colors["dark_slate_gray"] = dark_slate_gray;
	colors["DarkSlateGray"] = DarkSlateGray;
	colors["dark_slate_grey"] = dark_slate_grey;
	colors["DarkSlateGrey"] = DarkSlateGrey;
	colors["gray92"] = gray92;
	colors["grey92"] = grey92;
	colors["gray36"] = gray36;
	colors["grey36"] = grey36;
	colors["khaki1"] = khaki1;
	colors["pale_green"] = pale_green;
	colors["PaleGreen"] = PaleGreen;
	colors["gray100"] = gray100;
	colors["grey100"] = grey100;
	colors["gray44"] = gray44;
	colors["grey44"] = grey44;
	colors["DeepSkyBlue4"] = DeepSkyBlue4;
	colors["PaleTurquoise3"] = PaleTurquoise3;
	colors["turquoise"] = turquoise;
	colors["SlateGray4"] = SlateGray4;
	colors["goldenrod"] = goldenrod;
	colors["sandy_brown"] = sandy_brown;
	colors["SandyBrown"] = SandyBrown;
	colors["violet_red"] = violet_red;
	colors["VioletRed"] = VioletRed;
	colors["gray58"] = gray58;
	colors["grey58"] = grey58;
	colors["gray2"] = gray2;
	colors["grey2"] = grey2;
	colors["plum1"] = plum1;
	colors["cyan2"] = cyan2;
	colors["gray66"] = gray66;
	colors["grey66"] = grey66;
	colors["gray10"] = gray10;
	colors["grey10"] = grey10;
	colors["DarkSeaGreen3"] = DarkSeaGreen3;
	colors["AntiqueWhite3"] = AntiqueWhite3;
	colors["gray74"] = gray74;
	colors["grey74"] = grey74;
	colors["gray18"] = gray18;
	colors["grey18"] = grey18;
	colors["LemonChiffon2"] = LemonChiffon2;
	colors["sky_blue"] = sky_blue;
	colors["SkyBlue"] = SkyBlue;
	colors["blue2"] = blue2;
	colors["gray82"] = gray82;
	colors["grey82"] = grey82;
	colors["RosyBrown3"] = RosyBrown3;
	colors["forest_green"] = forest_green;
	colors["ForestGreen"] = ForestGreen;
	colors["pink1"] = pink1;
	colors["cyan3"] = cyan3;
	colors["tomato"] = tomato;
	colors["purple3"] = purple3;
	colors["maroon1"] = maroon1;
	colors["light_slate_blue"] = light_slate_blue;
	colors["LightSlateBlue"] = LightSlateBlue;
	colors["purple"] = purple;
	colors["coral"] = coral;
	colors["black"] = black;
	colors["gray0"] = gray0;
	colors["grey0"] = grey0;
	colors["IndianRed1"] = IndianRed1;
	colors["floral_white"] = floral_white;
	colors["FloralWhite"] = FloralWhite;
	colors["cornsilk4"] = cornsilk4;
	colors["DarkOliveGreen1"] = DarkOliveGreen1;
	colors["PaleTurquoise2"] = PaleTurquoise2;
	colors["medium_turquoise"] = medium_turquoise;
	colors["MediumTurquoise"] = MediumTurquoise;
	colors["DeepSkyBlue3"] = DeepSkyBlue3;
	colors["ghost_white"] = ghost_white;
	colors["GhostWhite"] = GhostWhite;
	colors["SlateGray3"] = SlateGray3;
	colors["medium_violet_red"] = medium_violet_red;
	colors["MediumVioletRed"] = MediumVioletRed;
	colors["wheat"] = wheat;
	colors["orchid4"] = orchid4;
	colors["lemon_chiffon"] = lemon_chiffon;
	colors["LemonChiffon"] = LemonChiffon;
	colors["LemonChiffon1"] = LemonChiffon1;
	colors["gray27"] = gray27;
	colors["grey27"] = grey27;
	colors["AntiqueWhite2"] = AntiqueWhite2;
	colors["DarkSeaGreen2"] = DarkSeaGreen2;
	colors["MistyRose4"] = MistyRose4;
	colors["gray91"] = gray91;
	colors["grey91"] = grey91;
	colors["gray35"] = gray35;
	colors["grey35"] = grey35;
	colors["light_grey"] = light_grey;
	colors["LightGrey"] = LightGrey;
	colors["light_gray"] = light_gray;
	colors["LightGray"] = LightGray;
	colors["light_sea_green"] = light_sea_green;
	colors["LightSeaGreen"] = LightSeaGreen;
	colors["gray99"] = gray99;
	colors["grey99"] = grey99;
	colors["gray43"] = gray43;
	colors["grey43"] = grey43;
	colors["RosyBrown2"] = RosyBrown2;
	colors["HotPink4"] = HotPink4;
	colors["light_goldenrod"] = light_goldenrod;
	colors["LightGoldenrod"] = LightGoldenrod;
	colors["gray"] = gray;
	colors["grey"] = grey;
	colors["gray42"] = gray42;
	colors["grey42"] = grey42;
	colors["purple2"] = purple2;
	colors["maroon2"] = maroon2;
	colors["medium_slate_blue"] = medium_slate_blue;
	colors["MediumSlateBlue"] = MediumSlateBlue;
	colors["LightCyan4"] = LightCyan4;
	colors["gray57"] = gray57;
	colors["grey57"] = grey57;
	colors["gray1"] = gray1;
	colors["grey1"] = grey1;
	colors["SlateGray1"] = SlateGray1;
	colors["turquoise4"] = turquoise4;
	colors["gray65"] = gray65;
	colors["grey65"] = grey65;
	colors["gray9"] = gray9;
	colors["grey9"] = grey9;
	colors["white"] = white;
	colors["gray73"] = gray73;
	colors["grey73"] = grey73;
	colors["gray17"] = gray17;
	colors["grey17"] = grey17;
	colors["cornsilk3"] = cornsilk3;
	colors["DarkOliveGreen2"] = DarkOliveGreen2;
	colors["RoyalBlue4"] = RoyalBlue4;
	colors["NavajoWhite3"] = NavajoWhite3;
	colors["cornsilk"] = cornsilk;
	colors["cornsilk1"] = cornsilk1;
	colors["gray81"] = gray81;
	colors["grey81"] = grey81;
	colors["DeepSkyBlue2"] = DeepSkyBlue2;
	colors["yellow_green"] = yellow_green;
	colors["YellowGreen"] = YellowGreen;
	colors["PaleTurquoise1"] = PaleTurquoise1;
	colors["misty_rose"] = misty_rose;
	colors["MistyRose"] = MistyRose;
	colors["MistyRose1"] = MistyRose1;
	colors["SlateGray2"] = SlateGray2;
	colors["beige"] = beige;
	colors["maroon"] = maroon;
	colors["SteelBlue4"] = SteelBlue4;
	colors["orchid3"] = orchid3;
	colors["blue_violet"] = blue_violet;
	colors["BlueViolet"] = BlueViolet;
	colors["ivory"] = ivory;
	colors["ivory1"] = ivory1;
	colors["dark_orange"] = dark_orange;
	colors["DarkOrange"] = DarkOrange;
	colors["DarkSeaGreen1"] = DarkSeaGreen1;
	colors["MistyRose3"] = MistyRose3;
	colors["AntiqueWhite1"] = AntiqueWhite1;
	colors["medium_sea_green"] = medium_sea_green;
	colors["MediumSeaGreen"] = MediumSeaGreen;
	colors["RosyBrown1"] = RosyBrown1;
	colors["old_lace"] = old_lace;
	colors["OldLace"] = OldLace;
	colors["dark_turquoise"] = dark_turquoise;
	colors["DarkTurquoise"] = DarkTurquoise;
	colors["HotPink3"] = HotPink3;
	colors["gold"] = gold;
	colors["purple1"] = purple1;
	colors["PaleVioletRed3"] = PaleVioletRed3;
	colors["LightCyan3"] = LightCyan3;
	colors["LightSkyBlue4"] = LightSkyBlue4;
	colors["turquoise3"] = turquoise3;
	colors["gray26"] = gray26;
	colors["grey26"] = grey26;
	colors["gray90"] = gray90;
	colors["grey90"] = grey90;
	colors["gray34"] = gray34;
	colors["grey34"] = grey34;
	colors["RoyalBlue3"] = RoyalBlue3;
	colors["NavajoWhite2"] = NavajoWhite2;
	colors["moccasin"] = moccasin;
	colors["cornsilk2"] = cornsilk2;
	colors["SpringGreen3"] = SpringGreen3;
	colors["gray98"] = gray98;
	colors["grey98"] = grey98;
	colors["gray25"] = gray25;
	colors["grey25"] = grey25;
	colors["gray33"] = gray33;
	colors["grey33"] = grey33;
	colors["light_slate_gray"] = light_slate_gray;
	colors["LightSlateGray"] = LightSlateGray;
	colors["light_slate_grey"] = light_slate_grey;
	colors["LightSlateGrey"] = LightSlateGrey;
	colors["PeachPuff4"] = PeachPuff4;
	colors["gray41"] = gray41;
	colors["grey41"] = grey41;
	colors["SteelBlue3"] = SteelBlue3;
	colors["burlywood"] = burlywood;
	colors["slate_blue"] = slate_blue;
	colors["SlateBlue"] = SlateBlue;
	colors["gray56"] = gray56;
	colors["grey56"] = grey56;
	colors["orchid2"] = orchid2;
	colors["orange"] = orange;
	colors["gray64"] = gray64;
	colors["grey64"] = grey64;
	colors["gray8"] = gray8;
	colors["grey8"] = grey8;
	colors["seashell4"] = seashell4;
	colors["aquamarine4"] = aquamarine4;
	colors["MistyRose2"] = MistyRose2;
	colors["gray72"] = gray72;
	colors["grey72"] = grey72;
	colors["gray16"] = gray16;
	colors["grey16"] = grey16;
	colors["LightSalmon2"] = LightSalmon2;

}

