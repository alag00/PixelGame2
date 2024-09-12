#include "levels.h"

void Levels::Load()
{
	// Audio
	songList[0] = LoadMusicStream("Assets/Audio/Music/CaveTheme.mp3");
	songList[1] = LoadMusicStream("Assets/Audio/Music/OminousSpook.mp3");
	songList[2] = LoadMusicStream("Assets/Audio/Music/MarchEcho.mp3");


	// TexturePack
	tileTextures[0] = LoadTexture("Assets/TileTextures/WorldTileTextures1.png");
	tileTextures[1] = LoadTexture("Assets/TileTextures/WorldTileTextures2.png");


	// Background
	backgroundTxrs[0][0] = LoadTexture("Assets/BackgroundTextures/CaveBackground1.png");
	backgroundTxrs[0][1] = LoadTexture("Assets/BackgroundTextures/CaveBackground2.png");
	backgroundTxrs[0][2] = LoadTexture("Assets/BackgroundTextures/CaveBackground3.png");

	backgroundTxrs[1][0] = LoadTexture("Assets/BackgroundTextures/ForestBackground1.png");
	backgroundTxrs[1][1] = LoadTexture("Assets/BackgroundTextures/ForestBackground2.png");
	backgroundTxrs[1][2] = LoadTexture("Assets/BackgroundTextures/ForestBackground3.png");

	backgroundTxrs[2][0] = LoadTexture("Assets/BackgroundTextures/SkyBackground1.png");
	backgroundTxrs[2][1] = LoadTexture("Assets/BackgroundTextures/SkyBackground2.png");
	backgroundTxrs[2][2] = LoadTexture("Assets/BackgroundTextures/SkyBackground3.png");

	backgroundTxrs[3][0] = LoadTexture("Assets/BackgroundTextures/CastleBackground1.png");
	backgroundTxrs[3][1] = LoadTexture("Assets/BackgroundTextures/CastleBackground2.png");
	backgroundTxrs[3][2] = LoadTexture("Assets/BackgroundTextures/CastleBackground3.png");

	backgroundTxrs[4][0] = LoadTexture("Assets/BackgroundTextures/SpookyForestBackground1.png");
	backgroundTxrs[4][1] = LoadTexture("Assets/BackgroundTextures/SpookyForestBackground2.png");
	backgroundTxrs[4][2] = LoadTexture("Assets/BackgroundTextures/SpookyForestBackground3.png");
}

void Levels::Unload()
{
	for (int i = 0; i < 2; i++)
	{
		UnloadTexture(tileTextures[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			UnloadTexture(backgroundTxrs[i][j]);
		}
	}
}

void Levels::SetCurrentBackground(int index)
{
	currentBackgrounds[0] = backgroundTxrs[index][0];
	currentBackgrounds[1] = backgroundTxrs[index][1];
	currentBackgrounds[2] = backgroundTxrs[index][2];
}

void Levels::CreateLevel(int level)
{
	switch (level)
	{
	case 1:
		CreateLevelOne();
		break;
	case 2:
		CreateLevelTwo();
		break;
	case 3:
		CreateLevelThree();
		break;
	case 4:
		CreateLevelFour();
		break;
	case 5:
		CreateLevelFive();
		break;
	case 6:
		CreateLevelSix();
		break;
	case 7:
		CreateLevelSeven();
		break;
	case 8:
		CreateLevelEight();
		break;
	case 9:
		CreateLevelNine();
		break;
	case 10:
		CreateLevelTen();
		break;
	}
}

void Levels::CreateLevelOne()
{


	currentLevel = "";

	bossChar = L'K';
	cutsceneID = 0;
	currentSong = songList[0];
	currentTileTxr = tileTextures[0];

	SetCurrentBackground(0);

	currentLevelWidth = 102;
	currentevelHeight = 36;

	currentLevel += "__##--##______________________________________________________________________________________________";
	currentLevel += "*o##--##***oooo******oo_****oooo*********ooooo***o*oo***___ooo*******o*oo**********_*ooo****ooo*_____*";
	currentLevel += "*o##-,##,,,=,cc,,.....oo*...,,,,B,=,,,,,,,,,,,,c,,,,,,,***oo,,,,,,,,,,,,coo*,,..,,*oocc,,,,,,c*ooo***o";
	currentLevel += "oo##,,#,,,,=,c,,.......o.....,,,B,=,,,,,.,c,,,,,cc,,,cc,*oo,,,,...,c,,,ccco,,,..,,,*,,ccc,,,,ccc,***oo";
	currentLevel += "o*#,c,,c,,,=,,,........o.......,B,=,,,,,..,cc,,,,cccc,,cc*,,,c,,.,c,,cccc,,,,....,,*,,,cccc,c,,,,,,oo*";
	currentLevel += "**,,ccc,,,,=,,..................B,=,,3,....,cc,,,,,c,cc,,*,,,cc,,,,,ccccc,,.......,,,,,,,cccc,,,,,,o**";
	currentLevel += "+,,,,cc,,,,=,...................B,=,,,,,...,,,,,,,cccc,,..,,,,ccc,,*ccc,,..........,,,,,ccccccc,,,,,**";
	currentLevel += "+,,,,,cc,,,=....................B.=,,C,,,,,,,,,,cccc,,......,,,,,,,*cc,,,,..........,,,cc,,ccccc,,,co*";
	currentLevel += "__##,,#ooo**...[b{.}..vK..{b]..[B.***o**,,,,,,,ccc,,v,.]b.{.b.,v,,o**,,,,.b[..Z.b..}.b,cc,,,,,ccc,c,oo";
	currentLevel += "**##,-##ooo****________________ooo***oo*,,,,ccccoo______________oooo**_____________________ooo,,cc,,oo";
	currentLevel += "**##--##*oooo*****__________ooooo**sssoo,,cc,cc,*oooo________o***oosooo*o_______________*oo*ooccc,,,*o";
	currentLevel += "*o##--##*sssss****ooooo******ooossssss**ccccc,,,**oo***o___oo****ssss**ooooo____**ooo__******cccc,,,o*";
	currentLevel += "oo##--##*ssssssssoooo********ssssssssso*cc..,,,c**oo****oooo**ssssssssoooo*********oooo**s**,,,,c,*ooo";
	currentLevel += "oo##--##*sssssssssssssssssssssssssssssoo,,.,,,cc**sssss**oo*sssssssssssssss******sss*oooss*o,,,,ccc*oo";
	currentLevel += "o*##--##*sssssssssssssssssssssssssssssoo,,,,,cc,**ssssssssssssssssssssssssssssssssssssssssoo,,,,,cccoo";
	currentLevel += "**##--##*sssssssssssssssssssssssssssssoo,,,,,,,,o*osssssssssssssssssssssssssssssssssssssss*o,,,,,,cc*o";
	currentLevel += "**##--##osssssssssssssssssssssssssssss*o,cc,,,,,*ooo*sssssssssssssssss*****************sss*oo*cc,,,c**";
	currentLevel += "**##--##osssssssssssssssssssssssssssss**,,ccc,,cc*oo*oo*ssssssssssssooo****ooo****oooo**oo***,,cc,,,oo";
	currentLevel += "**##--##osssssssssssssssssssssssssssoo*o,,,,ccc,,,,,oo*****sssssss*o***...............oo***,,,,,ccc,o*";
	currentLevel += "**##--##*sssssssssssssssssssssssssoo*oo,,,ccc,,cc,,,,,,*ooo***ss*oo**.....................,,,,,,,ccc**";
	currentLevel += "o*##--##*sssssssssssssssssssssssoo***,,,,,,,,,,..ccc,,cccc*ooo**o**........................,,c,,,ooo**";
	currentLevel += "oo##--##ossssssssssssssssssssss**ooc,,,,,cc,,,....,,ccccc,,,,*oo*...2......................,,cc,,,,ooo";
	currentLevel += "oo##,,##osssssssssssssssssssss***,,ccc,cccc,,...,,,,ccccc,,,,,,,............................,,cc,,,,oo";
	currentLevel += "*o##,,##o**ooosssssssssssssss*oo,ccccccc,,,,...,,,,c,,,,ccc,v,,,..}...[.b..]..b....Z..[.b{...,,,v,,,*o";
	currentLevel += "*##,,,,##***oooo*****oooo**oooo,,,ccccc,,,..{b].,,,,,,,,oo_______________________________________o****";
	currentLevel += "*#,cc,,cc,,,,**oo**oooo***ooo*,,,,ccc,c,**_____ooc,,,,,o*oo*_______*oo*_________________________oooo**";
	currentLevel += "oo,,cccccc,,,,,,,,,,,......,,,,,cccc,cc,***___o**cc,,,,****oo*___*oo**oo*****_________________*oo*ssss";
	currentLevel += "ooccc,,,cccccc,,,,,,......,,,,,cccc,,,,,*ooo**o**cccc,,**ss****o****ss****oooo***oooo***____*oo**sssss";
	currentLevel += "o*,..,,,,,ccc,,,,,,..}..[.,v,,ccc,,,,,,,,**ooo**,,,cccc*ossss*ooo*ssssssssss**ooooo**oooo******sssssss";
	currentLevel += "o*,,,1,,,,,,,oo*____________________o*,,,cccccc,,,,,cccoossssssssssssssssssssssssssssss**ooo*sssssssss";
	currentLevel += "**,.{S],*ooooo***oo*______________***oocccccc,,ccc,,,,,o*sssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "*oo____***oo***************************ooooo*******oooo**sssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "*oo*******o****ssssssssssssssssssssss********************sssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "*oo******sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

	
}

void Levels::CreateLevelTwo()
{
	currentLevel = "";
	cutsceneID = 0;
	currentSong = songList[1];
	currentTileTxr = tileTextures[0];

	SetCurrentBackground(1);

	currentLevelWidth = 128;
	currentevelHeight = 22;
	
	currentLevel += ".............................................................................................................................###";
	currentLevel += "............................................................................................................................####";
	currentLevel += "...........................................................................................................................#####";
	currentLevel += "%.........................................................................................................................xx####";
	currentLevel += "_...................................................................Zv...................................................#xxx#xx";
	currentLevel += "_...............................................................%%%%%%%%%...............................................###xxx##";
	currentLevel += "_%..............................................................._______............n.................Z................#x#######";
	currentLevel += "__.................................................v.............dddddd...........%%%%%..............%%%%..............#xx####xx";
	currentLevel += "__...............................................%%%%%............dddd............d___...............d__d..............##x##xxx#";
	currentLevel += "__............v....b.............................d___d............ddddddd.........ddd................dddd..............--y--yy-#";
	currentLevel += "__.........%%%%%%%%%%%...b..#--#...b..............dddd...........ddddd.dddd.....dddd..................ddddd....nZ..v...---yy---+";
	currentLevel += "__%.......%___________%%%%%%#--#%%%%%%..b.........dddddd........dddnZddd.ddd...ddd....................n.dddd%%%%%%%%%%%##y-yy--+";
	currentLevel += "___%......dd________________#--#______%%%%%........dddddd...v..%%%%%%%%%%%%dd.dddd............v.....%%%%%%%%____________########";
	currentLevel += "____%...ddd,cc***___________#--#___________%%%%..n.Z.dddd%%%%%%____________%%%%%ddd...Z.v...%%%%%%%%____________________________";
	currentLevel += "_____%dbdd,cc,,s**oo*_______#--#_______________%%%%%%%%%%_______________________%%%%%%%%%%%%____________________________________";
	currentLevel += "______%%%,cc,,Ss****ooo***__#--#________________________________________________________________________________________________";
	currentLevel += "_________%%*ooo***ss***oo***#--#________________________________________________________________________________________________";
	currentLevel += "___________**ooo*ssssssss***#--#*****___________________________***********________________________________*********************";
	currentLevel += "___________***ssssssssssssoo#--#************************************************************************************************";
	currentLevel += "_________*oo*sssssssssssss*o#--#**ss*****************************sssssssss**********************************ssssssssssssssssssss";
	currentLevel += "______ooo*oossssssssssssss**#--#**ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "__*******ossssssssssssssss**#DD#**ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	
	
}

void Levels::CreateLevelThree()
{
	currentLevel = "";
	bossChar = L'K';
	cutsceneID = 0;
	currentSong = songList[1];
	currentTileTxr = tileTextures[0];
	SetCurrentBackground(1);
	currentLevelWidth = 128;
	currentevelHeight = 22;

	currentLevel += "____##......................................................###..........................###..................................##";
	currentLevel += "_____##....................................................#x#x#........................#x#x#..................................+";
	currentLevel += "##x#####..................................................#x#x#x#......................#x#x#x#.................................+";
	currentLevel += "###xx###x................................................#########B...................#########..............................#x#";
	currentLevel += "#####x##x#................................................--yy---=.B..................=--y----................................#x";
	currentLevel += "#x###xxx###...............................................---y---=.B..................=---yy--................................##";
	currentLevel += "##xxx####xx...............................................---Cyy-=.B..................=---Z-y-................................#x";
	currentLevel += "####xx####x..............................................#########B...................#########..............................#x#";
	currentLevel += "######xx###..............................................#x#x#x#x#....................#x#x#x#x#...............................#x";
	currentLevel += "s---yyyy---..............................................##x#x#x##....................##x#x#x##...............................##";
	currentLevel += "sS-yyy---yy...v..b...n...b.Z....v.......................##x#x#x#x#..........vK........#x#x#x#x#...............................#x";
	currentLevel += "###########%%%%%%%%%%%%%%%%%%%%%%%%%%%..b................##_#_#_#_#######%%%%%%################..............................#x#";
	currentLevel += "______________________________________%%%%%..b...........#___________________________________##..............................##x";
	currentLevel += "___________________________________________%%%%....nZ....#___________________________________##..............................#x#";
	currentLevel += "_______________________________________________%%%%%%%%%%#___________________________________##..............................##x";
	currentLevel += "_____________________________________________________________________________________________##.............................##x#";
	currentLevel += "_____________________________________________________________________________________________##.............................#x#x";
	currentLevel += "_____________________________________________________________________________________________##.............................##x#";
	currentLevel += "_____________________________________________________________________________________________###............................#x#x";
	currentLevel += "______________________________________________________________________________________________##..........................##x#x#";
	currentLevel += "______________________________________________________________________________________________###....b...n...Z.v....b....##x#x#x";
	currentLevel += "______________________________________________________________________________________________####%%%%%%%%%%%%%%%%%%%%%%########";
	

}

void Levels::CreateLevelFour()
{
	currentLevel = "";
	bossChar = L'N';

	cutsceneID = 1;
	currentSong = songList[2];
	currentTileTxr = tileTextures[0];
	SetCurrentBackground(2);
	currentLevelWidth = 128;
	currentevelHeight = 64;

	currentLevel += "............####xxx##########xxxx######xxx#x########xxxx###########xxxx##xxxx............xx#.................xxxxxx#...........#";
	currentLevel += "............##xxx##########xxx###########xx########xx################xxx###xxx..........x#xx#...............xxxx####...........x";
	currentLevel += "............#xx----....y---....----....----....----....----....--------xx##--yy.........yy-yy..............yyyy--###...........x";
	currentLevel += "............xx#----....-yy-....----....----....----....----....---------#x-----VBy....yy-y--yy..........yyyy---y-###...........x";
	currentLevel += "............###----....--yy....----....----....----....----....---------#x-----BVyy..yyy---y--yy......yyy--yy----#x#...........#";
	currentLevel += "............###----....y---....----....----....---y....----....-------yy##-----VB-yyy--yy----y--y...yy-y---------#xx...........#";
	currentLevel += "............-------....-yy-....----....----....--yy....----....-----yyy-##y----BV-yy-----------y-yyy---yyy-------##x...........#";
	currentLevel += "............-------....--yy....----....----....--yy....----....----yy----=-yy--VB-yyy-------------yy-----yy-------=--.-.-.-.-.-+";
	currentLevel += "..........#.-C------..----yy..------..------..--yyyy..------..----yyyy---=-yyy-BV---yy---------N---yy---yy--------=------------+";
	currentLevel += "..........######xxxx#######xx#################xxxxx###############xxxxxxxxxxxx#######xx#################xxxx#######xx########xx#";
	currentLevel += "...........###xxx###########xxx#############xxxx####################xxxxxxx########xxxxxx##################xxx####xx#.........xx";
	currentLevel += "............#xx---------------yy-----------yyy--------y------yy--------yyyy--------yyyyyy------y------------xxxxxxx#...........x";
	currentLevel += "...xx##.....#xx--------------y--yy-y-----yyy--------yy--------y------y---yyy------yy.....y---yy---------------#xxxx#...........#";
	currentLevel += "...-xx-.....--------------------yyyyyy--y..yyy----yyy------yy-yy---yy-----yyyy--yyy.......y-yy-----------------##xxx...........#";
	currentLevel += "....----....-------------------y---yy-yy....yyyy-yy----------y.y-yy--------yyyyyyy........yyy-yyy---------------###x...........#";
	currentLevel += ".....----.####x#xx--------------y---yy..........yyy-------y--y.yy------------yyy...........yyy------------------###xx...........";
	currentLevel += "......-----##xx###xxx##xx##------yyy.............yy--------y-y..yy-y----------y............yy--y-----------------#xxx...........";
	currentLevel += "........----x#sss###xx##x#x------yy...yy...K...y...y--------y....yy----------yy..............yy------------------xxx#...........";
	currentLevel += ".........---##ssssssssss#xx------##xxx######x####xx##-------y....y---------yyy-yy..........yy-yy-----------------x###...........";
	currentLevel += "..........--##sssssssssssxxy-----###xxxxx###xxx###xxx-------y##x#yy-------yy-----yyyyyvKyyyy---yy----------------###............";
	currentLevel += "DDDDDDDDDDDD##sssssssssssx#-yy---##xssssssssssssss#xx---------xx--y------#####x#xx#x##x#x###x#######-------------###............";
	currentLevel += "............x#sssssssssss##---yy-##ssssssssssssssssx#--------------yy------########xxxxxxxxx#####xxx###----------###............";
	currentLevel += "............xxsssssssssss##-----y#x#ssssssssssssssxx#y--------------y-----------y-yyy....yyyy------yyxx###-------###............";
	currentLevel += "...........#xxsssssssssssx#------yxxssssssssssssssx#--y-----------y------------y-y...........yyy-yy--------------##xx...........";
	currentLevel += "...........#xssssssssssssx#-------#xx######xxx######---yy---y------y------------yy.............yy----------------#xx#...........";
	currentLevel += "...........xxssssssssss#xx#--------##xx#####xxxx###--yy-yy-y----y--y-y--------yyy-y...yn.K...y.y-----------Z-v---xxx#...........";
	currentLevel += "...........#x#ssssxxx##x##-----------yyy-----yy-------yy-y-y-----yy.y--y#########xxxxxxxxxxxxxxxxx############xxxxx##...........";
	currentLevel += "............#x##xx###xx#y--------------yyy----yy-------yy.y-------y.y-y-#####x##x##xxxxxxxxxx##x###x########xxxx####............";
	currentLevel += "............##xx###--yyy----------------yy-----y--------y..y----yy...y--x##xsssssssssssssssssssssssssssssssssssss###............";
	currentLevel += "............#xx------yy------------------yy-b-y--------y...y---y-y###y--xx#sssssssssssssssssssssssssssssssssssssss##............";
	currentLevel += "............xx#-----yy------------###################-yy###y------xx--y-xx#sssssssssssssssssssssssssssssssssssssss##............";
	currentLevel += "...........xx##----y----------C---###################yy--xx-y---------yy#xxsssssssssssssssssssssssssssssssssssssss#xx..........."; 
	currentLevel += "...........x###--yyy-------##########sssssssssssss###-------------------##xsssssssssssssss######xxxx###########sssxx#..........."; 
	currentLevel += "...........####yy----------#########sssssssssssssss##---y---------------#xx#ssssssss#xxx##########xxxxx##########xxx#...........";
	currentLevel += "...........###xyy--------############################----y----y----yyy--xx########xxxx#####-----yyyy----------###xx##...........";
	currentLevel += "............##x-yy--y-###############################----yy--y.y-yy--yy-x######xxxx##---------yyy--.-------------x##............";
	currentLevel += "............##x--yyy--####y-----yyy------------------------yyy.yy------------yyyy-----------yyy---...-------------##............";
	currentLevel += "............#x#-yy------yy-----yy---------------------------y..y-y---------yyyy------------yy------.----------------............";
	currentLevel += "............#x#yy------Z-yy---yyy---------K-----------------y...y--------yyyy-------------yyyy-K--------------------............";
	currentLevel += "...........##xxx########xxxx##xx############xx####x####-----y###y-----###xxxx############xxxx################xx-----............";
	currentLevel += "...........#x#xxxx####xxxx##xxxxx#############xxx#xxxx#---yy-#xx------#####xxxxx########xxxxxxxxx############xxxx###............";
	currentLevel += "...........####sssssssssssssssssssssssssssssssssss#xx#---y----xyy---yy-##sssssssssssssssssssssssssssssssssssss##xx##............";
	currentLevel += "...........###sssssssssssssssssssssssssssssssssssssxx#--yyy--...y--yy--##xsssssssssssssssssssssssssssssssssssssss#x#............";
	currentLevel += "............##sssssssssssssssssssssssssssssssssssss##--------...yyyyy---xxssssssssssssssssssssssssssssssssssssss####......##xx..";
	currentLevel += "............##sssssssssssssssssssssssssssssssssssss##--------...yyyy----xxsssssssssssssssssssssssssssssssssssss###-y.......xx...";
	currentLevel += "............##sssssssssssssssssssssssssssssssssssss#x-----.........y----x#sssssssssssssssssssssssssssssssssssss##-y........yy...";
	currentLevel += "............##ssssssssssssssssssssssssssssssssssssxx#-----.........y----###sssssssssssssssssss#xxxx#####xx#ssssx#-y.....--yyy...";
	currentLevel += "...........xx#ssssssssssssssssssssssssssssssss#xxx##---------...yyyy-----###xxxsssssss##xxxx#####xxxxx###xx###sxxx##----yyy.....";
	currentLevel += "...........#xxsssxxx###xx####xxxxx####x########x###y---------...y---yy----#xx##########xx##xx##-----------x######xx#yyyyy.......";
	currentLevel += "...........#x##xxx####x########xxxxxx##xx######---yy---------...y-----yy------#########------------.---------#####xxyy..........";
	currentLevel += "...........##xxx##-----------yy--------yy----------yyyy----.-...y.--------------------------------...---------------............";
	currentLevel += "............x##---.-----------yy--.--yyy------------yyyy--...y.y...---------------.---------------...---------------....###x....";
	currentLevel += "............###--...-----------yy...yyy---------------y.--...y.y...--.-----------...---------------.----------------.....xx.....";
	currentLevel += "............##x--...------------y...y-----------------..--...yyy...--..----------...--------------------K-----------.....yy.....";
	currentLevel += "............#xx--...-------------...y-----------------..--...-yy...--..---y------...---------####xxxx#######x##xx###....-yy.....";
	currentLevel += "............#xx--...-------------...-------------------.--...--y...--.--yy-------...--------y##xxxx#########xxx##x##..--yy......";
	currentLevel += "...........#xx#--y.yy------------y.y----------------------...---...---yyy---------.-------yyy#xxsssssssssssssssss###--y-y.......";
	currentLevel += "...........#x##-v-yyyyy---------yyy----Z-----v-------------.-----.--yyy--------Z--v-----yyy--##sssssssssssssssssss##-y-y........";
	currentLevel += "...........#######xxxyy----#####xxx#####xxxx###xx###---------Kv-----yyyy########xxx####yy----##sssssssssssssssssssx#yyy.........";
	currentLevel += "...........#x#####xx--yy--#xx######xxxxx#####xxx#######xxxx#########xxx#x########xxxx##y-y---##sssssssssssssssssss#xyy..........";
	currentLevel += "............xx#####s---yy#x#sssssssssssssssssssssss######xxxx#########xx#sssssssssss###---yy-##sssssssssssssssssssxxy...........";
	currentLevel += "............#xxx###sS---###ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssx#-----y##sssssssssssssssssss#x............";
	currentLevel += "............##xxx#########sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssxx------##sssssssssssssssssss##............";
	currentLevel += "............###xxxxx#####ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#xDDDDDD##sssssssssssssssssss##DDDDDDDDDDDD";

	
}

void Levels::CreateLevelFive()
{

	currentLevel = "";
	currentSong = songList[2];
	currentTileTxr = tileTextures[0];
	SetCurrentBackground(2);
	currentLevelWidth = 62;
	currentevelHeight = 16;

	currentLevel += "#ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#";
	currentLevel += "##ssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##";
	currentLevel += "######################################################ssssss##";
	currentLevel += "#######################################################ssss###";
	currentLevel += "####--....----....----....----....----....----....--###ssss###";
	currentLevel += "###---....----....----....----....----....----....---##ssss###";
	currentLevel += "###---....----....----....----....----....----....---###sss###";
	currentLevel += "###---....----....----....----....----....----....---#########";
	currentLevel += "s-----....----....----....----....----....----....----########";
	currentLevel += "sS----....----....----....----....----....----....-----------+";
	currentLevel += "s------..------..------..------..------..------..------------+";
	currentLevel += "##############################################################";
	currentLevel += "##############################################################";
	currentLevel += "###ssssssssssssssssssssssssssssssssssssssssssssssssssssssss###";
	currentLevel += "#ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

	
}



// First Spooky: From Castle to Spooky Land
void Levels::CreateLevelSix() // From Castle to Spooky Land
{
	// Tutorial for Grappling Hook
	// Tutorial for Wall Climb

	currentLevel = "";

	currentTileTxr = tileTextures[1];
	currentSong = songList[1];
	SetCurrentBackground(3);
	currentLevelWidth = 128;
	currentevelHeight = 60;
	cutsceneID = 0;

	bossChar = L'p';

	darkMode = false;

	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss#########################################sssssssssssssssssssssssssssssssssssss#############sssssssss";
	currentLevel += "sssssssssssssssssssssssssss###########################################sssssssssssssssssssssssssssssssssss###############ssssssss";
	currentLevel += "sssssssssssssssssssssssssss###....................L#L..............###ssssssssssss###########################.......#####sssssss";
	currentLevel += "sss##########################L.........K..........L#L.......Z......###sssssssss###########################............####ssssss";
	currentLevel += "#############################L....############....L#L....######....###ssssssss#####.....................................###sssss";
	currentLevel += "######.....................##L....L##########L....L#L....L####L....###sssssss###........................................###sssss";
	currentLevel += "#####......................##L....L##ssssss##L....L#L....L####L....####sssss###....G...........C........................###sssss";
	currentLevel += "#####......................l#L....L##ssssss##L....###....L####L....###########........#####################.............L##sssss";
	currentLevel += "#####......................l#L....L##ssssss##L...........L####L......########.........####################L.............L##sssss";
	currentLevel += "#####......DD....DD........##L....L##ssssss##L...........L####L.......................###ssssssssssssss###L....DDDDD....L##sssss";
	currentLevel += "####s......##....##........###....L##ssssss##L...........L####L.......................##ssssssssssssssss##L....#####....L##sssss";
	currentLevel += "####sS.....##....##...............L##ssssss##L...........L####L.......................##ssssssssssssssss##L.............L##sssss";
	currentLevel += "#####################.............L##ssssss##L...........L####L............Z..........##ssssssssssssssss##L.............L##sssss";
	currentLevel += "#####################################ssssss###DDDDDDDDDDD######DDDDDDDD#######........##ssssssssssssssss##L.............L##sssss";
	currentLevel += "#####sssssssssssssss#################ssssss###################################........##ssssssssssssssss##L.............L##sssss";
	currentLevel += "###sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##........##ssssssssssssssss###DDDD.....#######sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##........##ssssssssssssssss#######........####sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##........##ssssssssssssssss####............l##sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##DDDDDDDD##ssssssssssssssss##L......DDD....###sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss############ssssssssssssssss##L......###DD..###sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##L........###DD###sssss";
	currentLevel += "sssssssss############################ssssssssssssssssssss################################sssssssssssssss##L..........######sssss";
	currentLevel += "sssss####################################ssssssssssss#########################################ssssssssss##L............####sssss";
	currentLevel += "sss#######..........................######################..............................#######sssssssss##L.............l##sssss";
	currentLevel += "sss##...................................##############.......................................##sssssssss##L.............###sssss";
	currentLevel += "sss##........................................................................................l##ss#########DDDDDD.......###sssss";
	currentLevel += "sss##..................................................G.....................................####################.......###sssss";
	currentLevel += "sss##..........................................C.................G............................#####.....................###sssss";
	currentLevel += "sss##......................................########........................G........................................Z...####ssss";
	currentLevel += "sss#r......................................l######r..................................G...................#####################ss";
	currentLevel += "sss##............................G.........########.................................................##########################ss";
	currentLevel += "sss##......................................########...........................................###########sssssssssssssssssssssss";
	currentLevel += "sss##......................................########...........................................l#####ssssssssssssssssssssssssssss";	
	currentLevel += "sss##..............G.......................########...........................................###sssssssssssssssssssssssssssssss";
	currentLevel += "sss##.....##...##..........................########...........................................##ssssssssssssssssssssssssssssssss";
	currentLevel += "sss##DDDDD##...##DDDDDDDDDDDDDDDDDDDDDDDDDD########DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD##ssssssssssssssssssssssssssssssss";
	currentLevel += "sss#########...#############################################################################################ssssssssssssssssssss";
	currentLevel += "sss#########...##########################################################################################################sssssss";
	currentLevel += "ssssssssss##...##sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#######################################sssss";
	currentLevel += "ssssssssss##...##sssssssssssssssssssssssssssssssssssssssssssssss#################################..............=...#########ssss";
	currentLevel += "ssssssssss##...##ssssssssssssssssssssssssssssssss####################################...B......................=.........####sss";
	currentLevel += "ssssssssss##...##ssssssssssssssssssssss##########################...................=...B......................=...........###ss";
	currentLevel += "ssssssssss##...##ssssssssssssssss#################..................................=...B......................=............##ss";
	currentLevel += "ssssssssss##...##ssssssssssss###########............................................=...B......................=............###s";
	currentLevel += "ssssssssss##...##sssssssss########..................................................=...B......................=............###s";
	currentLevel += "ssssssssss##...##sssssss######......................................................=...B......................=.............##s";
	currentLevel += "ssssssssss##...##ssssss####.........................................................=...B......................=.............##s";
	currentLevel += "ssssssssss##...##sssss###...........................................................=...B......................=.............##s";
	currentLevel += "ssssssssss##...##ssss###............................................................=...B......................=.............##s";
	currentLevel += "ssssssssss##...##sss###............................................................G=...B............p.........=.............##s";
	currentLevel += "ssssssssss##...#######..............................................................=...####################...=.............##s";
	currentLevel += "ssssssssss##...#######....................................................G.........=...####################...=.............###";
	currentLevel += "ssssssssss##...............................................G........................=....##ssssssssssssss##....=....G........###";
	currentLevel += "ssssssssss##.................................G......................................=.....##ssssssssssss##.....=..............+#";
	currentLevel += "ssssssssss##.....................G..................................................=.....##ssssssssssss##.....=..............+#";
	currentLevel += "ssssssssss##############............................................................=.....##ssssssssssss##DDDDDDDDDDDDDDDD######";
	currentLevel += "ssssssssss##############DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD##ssssssssssss##ssssssssssssssssssssss";
	


}

void Levels::CreateLevelSeven()
{
	currentLevel = "";

	currentTileTxr = tileTextures[1];
	currentSong = songList[1];

	bossChar = L'p';
	SetCurrentBackground(4);
	currentLevelWidth = 192;
	currentevelHeight = 26;
	cutsceneID = 0;

	darkMode = false;

	currentLevel += "................................................................................................=.B.................B........=............................________.............................+";
	currentLevel += "................................................................................................=.B.................B........=............................________.............................+";
	currentLevel += "................................................................................................=.B.................B........=............................________.............................+";
	currentLevel += "................................................................................................=.B.................B........=............................________.............................+";
	currentLevel += "................................................................................................=.B.................B........=............................________.................G...........+";
	currentLevel += "................................................................................................=.B.................B........=}}}}}}}}}}}}}}}}}}}}}.......________.............................+";
	currentLevel += "................................................................................................=.B.................B........%%%%%%%%%%%%%%%%%%%%%%........______..............................+";
	currentLevel += "................................................................................................=.B.................B........L_____________________.......................G.................}}}+";
	currentLevel += "................................................................................................=}B}}}}}}}p}}}}}}}}}B........L_____________________......................................}}}%%%%";
	currentLevel += "........................................................G.......................................%%%%%%%%%%%%%%%%%%%%%%=======L_____________________D.....................................%%%____";
	currentLevel += "........................................G..................................G...................._____________________L.......L_____________________%..........G....................DDDDDD_______";
	currentLevel += "%..............................................................................}.C.}............_____________________L.......L______________________.........................DDDDDD%%%%%%_______";
	currentLevel += "_.........................###.................####............................%%%%%%............_____________________L.......L______________________DDDD.............DDDDDDDD%%%%%%_____________";
	currentLevel += "_%........................##L.................####.................G..........L_____.............____________________L.......L______________________%%%%DDDDDDDDDDDDD%%%%%%%%___________________";
	currentLevel += "#_........................##L....###..........####............................L_____.............____________________L.......L__________________________%%%%%%%%%%%%%___________________________";
	currentLevel += "##........................##L....L##..........####............................L_____%..............___________________.......L__________________________________________________________________";
	currentLevel += "sS........................##L....L##..........####............................L______........................................L__________________________________________________________________";
	currentLevel += "s}}}}}}...................###....L###.........####............................L______}}}}....................................L__________________________________________________________________";
	currentLevel += "####%%%}}}}}}}}}..........---....L###..{.[.}..####......G.....................L______%%%%}}}}}}Z}}}}}}}}}}Z}}}}}}}}}}Z}}}}}}}L__________________________________________________________________";
	currentLevel += "####___%%%%%%%%%}}}}}}}}}}---}}}}L###*************............................___________%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%___________________________________________________________________";
	currentLevel += "________________%%%%%%%%%%%%%%%%%****,,,,,,,,,,,**............................__________________________________________________________________________________________________________________";
	currentLevel += "________________________________*,,,,,,,,,,,,,,,,*............................__________________________________________________________________________________________________________________";
	currentLevel += "_______________________________*,,,,,,,,,,,,,,,,,*.................G..........__________________________________________________________________________________________________________________";
	currentLevel += "______________________________*,,,,,,,,,,,,,,,,,,*............................__________________________________________________________________________________________________________________";
	currentLevel += "_____________________________*,,,,,,,,,,,,,,,,,,,*............................__________________________________________________________________________________________________________________";
	currentLevel += "_____________________________*,,,,,,,,,,,,,,,,,,,*DDDDDDDDDDDDDDDDDDDDDDDDDDDD__________________________________________________________________________________________________________________";
}

void Levels::CreateLevelEight()
{
	currentLevel = "";

	currentTileTxr = tileTextures[1];
	currentSong = songList[1];
	SetCurrentBackground(4);
	currentLevelWidth = 192;
	currentevelHeight = 22;
	bossChar = L'P';
	cutsceneID = 2;

	darkMode = false;

	currentLevel += ".....................................%____******sssssssssssssssssssssssssssssssssssssssssssss***************#####################################################################sssssssssssssss";
	currentLevel += "...................................%%___********sssssssssssssssssssssssssssssssssssssssssssss************########################################################################sssssssssssssss";
	currentLevel += ".................................%%___**,,,,,,***ssssssssssssssssssssssssssssssssssssssss********,,,,,------------------------------------=--------------VVBB------------------##sssssssssssssss";
	currentLevel += "................................%__,,,,,,,,,,,,***sssssssssssssssssssssssssssssssssssssss*****,,,,,,------------C-------------------------=------------VVBB--------------------##sssssssssssssss";
	currentLevel += "...............................%_,,,,,,,,,,,,,,,**sssssssssssssssssssssssssssssss*********,,,,,,,,,,-G-------##############################----------VVBB----------------------##sssssssssssssss";
	currentLevel += "..............................._,,,,,,,,,,,,,,,,**ssssssssssssssssss******************,,,,,,,,,,,,,,------#################################--------VVBB------------------------##sssssssssssssss";
	currentLevel += "..............................%_,,,,,,,,,,,,,,,,**ssssssssssssssss****************,,,,,,,,,,,,,,,,,,,,------####ssssssssssssssssssssssss###------VVBB--------------------------##sssssssssssssss";
	currentLevel += ".............................._L,,,,,,,,,,,,,,,,**sssssssssssssss***,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,-----###ssssssssssssssssssssssss##----VVBB----------------------------##sssssssssssssss";
	currentLevel += ".............................._L,,,,,,,,,,,,,,,,**sssssssssssss***,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,----###sssssssssssssssssssssss##--VVBB------------------------------##ssssssssssssss*";
	currentLevel += ".............................._L,,,__,,,,,,,,,,,**sssssssssss****,,,,,,G,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,----###ssssssssssssssssssssss##VVBB--------------------------------##ssssssssssssss*";
	currentLevel += ".............................._L,,,L_,,,,,,,,,,,**sssssssss*****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,--L##ssssssssssssssssssssss##BB----------------------------------##############***";
	currentLevel += ".............................._L,,,L_,,,,,,,,,,,***sssssss****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,G,,,,L##ssssssssssssssssssssss##------------------------------------############*****";
	currentLevel += "..............................##,,,L_,,,,,,,,,,,,**ssssss***,,,,,,,,,,,,DDDD,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,L##ssssssssssssssssssssss##------------------------------------=-----------,,,,+";
	currentLevel += "s................................,,L_,,,,,,,,,,,,**********,,,,,,,,,,,,,****DD,,,,,,G,,,,,,,,,,,,,,,,,,,,,,,,,,,**#ssssssssssssssssssssss##------------------------------------=------------,,,+";
	currentLevel += "s.S}}}...................}}}}Z}}}}}L_D,,,,,,,,,,,,********,,,,,,,G,,,,,,******D,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssssssssssssssssss##------------------------------------#############****";
	currentLevel += "%%%%%%}}}Z}}}}}K}}}}}}}}}%%%%%%#####**D,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,DD**s****D,,,,,,,,,,,,,,,,G,,,,,,,,,,,,,,,**sssssssssssssssssssssss##------------------------------------###############**";
	currentLevel += "______%%%%%%%%%%%%%%%%%%%____________**DD,,,,,,,,,,,,,,,,,,,,,,,,,,,,,****sss***DDD,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssssssssssssssssss##------------------P-----------------##ssssssssssssss*";
	currentLevel += "_____________________________________****DD,,,,,,,,,,G,,,,,,,,,,,,,DDD***sssss*****DDDD,,,,,,,,,,,,,,,,,,,DDDDDD**sssssssssssssssssssssss########################################sssssssssssssss";
	currentLevel += "______________________________________*****DDD,,,,,,,,,,,,,,,,,,,DD*****sssssss********DDDDDDDDDDDDDDDDDDD********sssssssssssssssssssssss########################################sssssssssssssss";
	currentLevel += "________________________________________******DDDDDDDD,,,,,,,,,DD******sssssssssss*******************************sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "__________________________________________************DDDDDDDDD*****ssssssssssssssssss*********************sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "________________________________________________******************ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

}



// Spooky Level: Spooky land
void Levels::CreateLevelNine() 
{

	currentLevel = "";

	currentTileTxr = tileTextures[0];
	currentSong = songList[0];
	SetCurrentBackground(0);
	currentLevelWidth = 128;
	currentevelHeight = 52;
	cutsceneID = 0;

	bossChar = L'K';

	darkMode = true;

	
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssss*********************************************************ssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssss*****************************************************************sssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss*********.......................................................*****ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssss******................................G..............................**ssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssss****...................................................................+ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssss***.............................................Z.......................+ssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*************..........................................*****************************ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*************...................***......................****************************ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L........................................***............***ssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L...................***.................................**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L.......................................................**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L......********.........................................**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L......L*********.......................................**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L......L***sss***.......................................**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L......L**sssss**...............W.......W...............**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L......L**sssss***************************************..**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L......L**ssssss**************************************..**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssss***L......***sssssssssssssssssssssssssssssssssssssssss***..**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssss********......***ssssssssssssssssssssssssssssssssssssssssss**..**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssss*******.........***ssssssssssssssssssssssssssssssssssssssssss**..**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss****.............***ssssssssssssssssssssssssssssssssssssssssss**..**sssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss***.............***sssssssssssssssssssssssssssssssssssssssssss**..***ssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**...........******sssssssssssssssssssssssssssssssssssssssssss**..*********ssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**.............*****sssssssssssssssssssssssssssssssssssssssss***...***********sssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss***..............****ssssssssssssssssssssssssss*****************..........***********ssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss******............*********************************************..............*************sssssssssssssssssss";
	currentLevel += "sssssssssssssssssss****................****************************....................................********sssssssssssssssss";
	currentLevel += "sssssssssssssssssss***......................................................................................****ssssssssssssssss";
	currentLevel += "sssssssssssssssssss****.......K......................Z........................................................***sssssssssssssss";
	currentLevel += "ssssssssssssssssssss***********************************************.............**......***....................***ssssssssssssss";
	currentLevel += "ssssssssssssssssssssss***********************************************...........**......**L....................***ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss***....**.....**......**L.....************...L**ssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssss******************************ssssssss**....**.....**......**L.....L**********L...L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss********************************sssssss**....**.....**......**L.....L***ssss***L...L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss***...........................***ssssss**....**.....**......**L.....L**ssssss**L...L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L............................**ssssss**....**.....**......**L.....L**ssssss**L...L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L.............K..............**ssssss**....**.....**......***.....L**ssssss**L...L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L...********************...***sssssss**...........................L**ssssss**L...L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L...L*******************...**ssssssss**..............W............L**ssssss***.G.L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L...L***sssssssssssss***...**ssssssss********************************ssssss***...L**ssssssssssssss";
	currentLevel += "ssssssssssssssss**************L...L**sssssssssssssss**...**sssssssss******************************ssssss***....***ssssssssssssss";
	currentLevel += "sssssssssssssss****************...L**sssssssssssssss**...**ssssssssssssssssssssssssssssssssssssssssssss****....***ssssssssssssss";
	currentLevel += "ssssssssssssss****................L**sssssssssss******...*************************************************.....***ssssssssssssss";
	currentLevel += "ssssssssssssss**..................L**ssssssssss*******...************************************************......***ssssssssssssss";
	currentLevel += "ssssssssssssssss..................L**ssssssssss**..............................................................***ssssssssssssss";
	currentLevel += "ssssssssssssssssS.................L**ssssssssss**...............W...W.........W.........W.......W..............***ssssssssssssss";
	currentLevel += "ssssssssssssss***********************ssssssssss*******************************************************************ssssssssssssss";
	currentLevel += "ssssssssssssss***********************sssssssssss*****************************************************************sssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";


}

void Levels::CreateLevelTen()
{

	currentLevel = "";
	currentSong = songList[2];
	currentTileTxr = tileTextures[1];
	SetCurrentBackground(4);
	currentLevelWidth = 62;
	currentevelHeight = 16;

	currentLevel += "#ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#";
	currentLevel += "##ssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##";
	currentLevel += "######################################################ssssss##";
	currentLevel += "#######################################################ssss###";
	currentLevel += "####--....----....----....----....----....----....--###ssss###";
	currentLevel += "###---....----....----....----....----....----....---##ssss###";
	currentLevel += "###---....----....----....----....----....----....---###sss###";
	currentLevel += "###---....----....----....----....----....----....---#########";
	currentLevel += "s-----....----....----....----....----....----....----########";
	currentLevel += "sS----....----....----....----....----....----....-----------+";
	currentLevel += "s------..------..------..------..------..------..------------+";
	currentLevel += "##############################################################";
	currentLevel += "##############################################################";
	currentLevel += "###ssssssssssssssssssssssssssssssssssssssssssssssssssssssss###";
	currentLevel += "#ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

}
