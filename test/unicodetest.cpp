/*
 The translated text was taken from http://www.columbia.edu/kermit/utf8.html
*/

#include <vector>

#include "paragui.h"
#include "pgapplication.h"
#include "pglabel.h"
#include "pgfont.h"

// If unicode is disabled, PG_String becomes the standard std::string class
#include "pgstring.h"


#ifndef ENABLE_UNICODE
#include <iostream>
#warning UNICODE support disabled!

int main( int argc, char **argv ) {
	std::cout << "UNICODE support disabled" << std::endl;
	return 0;
}

#else

int main( int argc, char **argv )
{
	PG_Application app;
	
	// The theme must have a font that has all the glyphs we will be using mapped to
	//  the appropriate unicode characters (Arial Unicode MS for example, it has most of
	//  the unicode ranges).
	// "default" has the Vera font that only covers the Latin ranges.
	app.LoadTheme("default");

	app.InitScreen( 640, 480, 0 );
	app.SetCaption("ParaGUI with Unicode Support", NULL);
	
	int currentY = 0;
	const int H = 20;
	PG_Label * en = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// utf-8 can be considered a superset of ASCII so ASCII text
	// can of course be passed
	en->SetText("English: I can eat glass and this doesn't hurt me.");
	en->Show();
	
	PG_Label * ch = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	ch->SetText("Chinese: 我能吞下玻璃而不伤身体。");
	ch->Show();
	
	
	// Using Unicode codes for building a string
	std::vector<PG_Char> someCharArray;
	
	// Adding characters by code
	someCharArray.push_back(0x0645);
	someCharArray.push_back(0x0646);
	
	// Adding utf8 encoded characters (They are multibyte characters)
	someCharArray.push_back(PG_Char("ح"));
	someCharArray.push_back(PG_Char("م"));
	
	// Adding regular one byte characters
	someCharArray.push_back(PG_Char('A'));
	
	// Constructing the string
	PG_String ustr(someCharArray);
	
	PG_Label * ar = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	ar->SetText("Arabic:  أنا قادر على أكل الزجاج و هذا لا يؤلمني.");
	// appending the previosuly built text in ustr to the PG_Label
	ar->SetText((ar->GetText() + ustr + "  Some More Text").utf8().c_str());
	ar->Show();
	
	
	
	PG_Label * ru = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	ru->SetText("Russian: Я могу есть стекло, оно мне не вредит.");
	ru->Show();

	PG_Label * ge = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	ge->SetText("Georgian: მინას ვჭამ და არა მტკივა.");
	ge->Show();
	
	PG_Label * am = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	am->SetText("Armenian: Կրնամ ապակի ուտել և ինծի անհանգիստ չըներ։");
	am->Show();
	
	PG_Label * th = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	th->SetText("Thai: ฉันกินกระจกได้ แต่มันไม่ทำให้ฉันเจ็บ");
	th->Show();
	
	PG_Label * jp = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	jp->SetText("Japanese: 私はガラスを食べられます。それは私を傷つけません。");
	jp->Show();
	
	PG_Label * kr = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	kr->SetText("Korean: 나는 유리를 먹을 수 있어요. 그래도 아프지 않아요");
	kr->Show();
	
	PG_Label * gr = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	gr->SetText("Greek: Μπορώ να φάω σπασμένα γυαλιά χωρίς να πάθω τίποτα.");
	gr->Show();
	
	PG_Label * hi = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	hi->SetText("Hindi: मैं काँच खा सकता हूँ, मुझे उस से कोई पीडा नहीं होती. ");
	hi->Show();

	PG_Label * uk = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	uk->SetText("Ukrainian: Я можу їсти шкло, й воно мені не пошкодить.");
	uk->Show();
	
	PG_Label * he = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	he->SetText("Hebrew: אני יכול לאכול זכוכית וזה לא מזיק לי.");
	he->Show();
	
	PG_Label * du = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	du->SetText("Dutch: Ik kan glas eten, maar dat doet mĳ geen kwaad.");
	du->Show();
	
	PG_Label * pl = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	pl->SetText("Polish: Mogę jeść szkło, i mi nie szkodzi.");
	pl->Show();
	
	PG_Label * fr = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	fr->SetText("French: Je peux manger du verre, ça ne me fait pas de mal.");
	fr->Show();

	PG_Label * sp = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	sp->SetText("Spanish: Puedo comer vidrio, no me hace daño. ");
	sp->Show();
	
	PG_Label * fa = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	fa->SetText("Farsi / Persian: .من می توانم بدونِ احساس درد شيشه بخورم");
	fa->Show();
	
	PG_Label * no = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	no->SetText("Tibetan: ཤེལ་སྒོ་ཟ་ནས་ང་ན་གི་མ་རེད། ");
	no->Show();
	
	PG_Label * de = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	de->SetText("Deutsch / German: Ich kann Glas essen, ohne mir weh zu tun.");
	de->Show();
	
	PG_Label * ma = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	ma->SetText("Macedonian: Можам да јадам стакло, а не ме штета.");
	ma->Show();
	
	PG_Label * cz = new PG_Label(NULL, PG_Rect(10, currentY+=H,620,20));
	// Passing utf-8 encoded text directly
	cz->SetText("Czech: Mohu jíst sklo, neublíží mi.");
	cz->Show();
	
	app.Run();
	
	delete en;
	delete ch;
	delete ar;
	delete ru;
	delete ge;
	delete am;
	delete th;
	delete jp;
	delete kr;
	delete gr;
	delete hi;
	delete uk;
	delete he;
	delete du;
	delete pl;
	delete fr;
	delete sp;
	delete fa;
	delete no;
	delete de;
	delete ma;
	delete cz;
	
	return 0;
}

#endif // UNICODE_ENABLED
