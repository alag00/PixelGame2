#include "levels.h"

void Levels::Load()
{
	// Audio
	songList[0] = LoadMusicStream("Assets/Audio/Music/CaveTheme.mp3");
	songList[1] = LoadMusicStream("Assets/Audio/Music/OminousSpook.mp3");
	songList[2] = LoadMusicStream("Assets/Audio/Music/MarchEcho.mp3");
	cutsceneSong = LoadMusicStream("Assets/Audio/Music/CutsceneTheme.mp3");

	bossSongList[0] = LoadMusicStream("Assets/Audio/Music/BossTheme.mp3");
	bossSongList[1] = LoadMusicStream("Assets/Audio/Music/GnobTheme.mp3");


	// TexturePack
	tileTextures[0] = LoadTexture("Assets/TileTextures/WorldTileTextures1.png");
	tileTextures[1] = LoadTexture("Assets/TileTextures/WorldTileTextures2.png");
	tileTextures[2] = LoadTexture("Assets/TileTextures/WorldTileTextures3.png");
	tileTextures[3] = LoadTexture("Assets/TileTextures/WorldTileTextures4.png");

	// Background
	backgroundTxrs[0][0] = LoadTexture("Assets/BackgroundTextures/CaveBackground1Alter.png");
	backgroundTxrs[0][1] = LoadTexture("Assets/BackgroundTextures/CaveBackground2Alter.png");
	backgroundTxrs[0][2] = LoadTexture("Assets/BackgroundTextures/CaveBackground3Alter.png");

	backgroundTxrs[1][0] = LoadTexture("Assets/BackgroundTextures/ForestBackground1Alter.png");
	backgroundTxrs[1][1] = LoadTexture("Assets/BackgroundTextures/ForestBackground2Alter.png");
	backgroundTxrs[1][2] = LoadTexture("Assets/BackgroundTextures/ForestBackground3Alter.png");

	backgroundTxrs[2][0] = LoadTexture("Assets/BackgroundTextures/SkyBackground1Alter.png");
	backgroundTxrs[2][1] = LoadTexture("Assets/BackgroundTextures/SkyBackground2Alter.png");
	backgroundTxrs[2][2] = LoadTexture("Assets/BackgroundTextures/SkyBackground3Alter.png");

	backgroundTxrs[3][0] = LoadTexture("Assets/BackgroundTextures/CastleBackground1Alter.png");
	backgroundTxrs[3][1] = LoadTexture("Assets/BackgroundTextures/CastleBackground2Alter.png");
	backgroundTxrs[3][2] = LoadTexture("Assets/BackgroundTextures/CastleBackground3Alter.png");

	backgroundTxrs[4][0] = LoadTexture("Assets/BackgroundTextures/SpookyForestBackground1Alter.png");
	backgroundTxrs[4][1] = LoadTexture("Assets/BackgroundTextures/SpookyForestBackground2Alter.png");
	backgroundTxrs[4][2] = LoadTexture("Assets/BackgroundTextures/SpookyForestBackground3Alter.png");

	backgroundTxrs[5][0] = LoadTexture("Assets/BackgroundTextures/SnowyMountainBackground1.png");
	backgroundTxrs[5][1] = LoadTexture("Assets/BackgroundTextures/SnowyMountainBackground2.png");
	backgroundTxrs[5][2] = LoadTexture("Assets/BackgroundTextures/SnowyMountainBackground3.png");
}

void Levels::Unload()
{
	for (int i = 0; i < 4; i++)
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

void Levels::QueueLevelParticles(int level)
{
	switch (level)
	{
	case 2:
	case 3:
		particleRef->QueueParticle(FALLING_LEAVES, Vector2(0.f, 0.f));
		break;
	case 13:
		particleRef->QueueParticle(FALLING_SNOW, Vector2(0.f, 0.f));
		break;
	}
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
	case 11:
		CreateLevelEleven();
		break;
	case 12:
		CreateLevelTwelve();
		break;
	case 13:
		CreateLevelThirteen();
		break;
	case 14:
		CreateLevelFourteen();
		break;
	case 15:
		CreateLevelFifteen();
		break;
	}
}

void Levels::CreateLevelOne()
{


	currentLevel = "";

	bossChar = L'K';
	spawnChar = L'.';
	cutsceneID = 1;
	currentSong = songList[0];
	currentBossSong = bossSongList[0];
	currentTileTxr = tileTextures[0];
	startCutscene = true;

	SetCurrentBackground(0);

	currentLevelWidth = 102;
	currentevelHeight = 36;
	miscChar = L',';

	currentLevel += "__##--##______________________________________________________________________________________________";
	currentLevel += "*o##--##***oooo******oo_****oooo*********ooooo***o*oo***___ooo*******o*oo**********_*ooo****ooo*_____*";
	currentLevel += "*o##-,##,,,=,cc,,.....oo*...,,,,B,=,,,,,,,,,,,,c,,,,,,,***oo,,,,,,,,,,,,coo*,,..,,*oocc,,,,,,c*ooo***o";
	currentLevel += "oo##,,#,,,,=,c,,.......o.....,,,B,=,,,,,.,c,,,,,cc,,,cc,*oo,,,,...,c,,,ccco,,,..,,,*,,ccc,,,,ccc,***oo";
	currentLevel += "o*#,c,,c,,,=,,,........o.......,B,=,,,,,..,cc,,,,cccc,,cc*,,,c,,.,c,,cccc,,,,....,,*,,,cccc,c,,,,,,oo*";
	currentLevel += "**,,ccc,,,,=,,..................B,=,,3,....,cc,,,,,c,cc,,*,,,cc,,,,,ccccc,,.......,,,,,,,cccc,,,,,,o**";
	currentLevel += "+,,,,cc,,,,=,...................B,=,,,,,...,,,,,,,cccc,,..,,,,ccc,,*ccc,,..........,,,,,ccccccc,,,,,**";
	currentLevel += "+,,,,,cc,,,=,...................B,=,,C,,,,,,,,,,cccc,,......,,,,,,,*cc,,,,..........,,,cc,,ccccc,,,co*";
	currentLevel += "__##,,#ooo**,..[b{.}..vK..{b]..[B,***o**,,,,,,,ccc,,v,.]b.{.b.,v,,o**,,,,.b[..Z.b..}.b,cc,,,,,ccc,c,oo";
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
	currentLevel += "*o##,,##o**ooosssssssssssssss*oo,ccccccc,,,,...,,,,c,,,,ccc,v,,,n.}...[.b..]..b....Z..[.b{...,,,v,,,*o";
	currentLevel += "*##,,,,##***oooo*****oooo**oooo,,,ccccc,,,..{b].,,,,,,,,oo_______________________________________o****";
	currentLevel += "*#,cc,,cc,,,,**oo**oooo***ooo*,,,,ccc,c,**_____ooc,,,,,o*oo*_______*oo*_________________________oooo**";
	currentLevel += "oo,,cccccc,,,,,,,,,,,......,,,,,cccc,cc,***___o**cc,,,,****oo*___*oo**oo*****_________________*oo*ssss";
	currentLevel += "ooccc1,,cccccc,,,,,,......,,,,,cccc,,,,,*ooo**o**cccc,,**ss****o****ss****oooo***oooo***____*oo**sssss";
	currentLevel += "o*,,..,,,,ccc,,,,,,n.}..[.,v,,ccc,,,,,,,,**ooo**,,,cccc*ossss*ooo*ssssssssss**ooooo**oooo******sssssss";
	currentLevel += "o*,..,,,,,,,,oo*____________________o*,,,cccccc,,,,,cccoossssssssssssssssssssssssssssss**ooo*sssssssss";
	currentLevel += "**,{.S],*ooooo***oo*______________***oocccccc,,ccc,,,,,o*sssssssssssssssssssssssssssssssssssssssssssss";
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
	spawnChar = L',';
	SetCurrentBackground(1);
	startCutscene = false;
	

	currentLevelWidth = 128;
	currentevelHeight = 22;
	
	currentLevel += "................................................................................................................................";
	currentLevel += "................................................................................................................................";
	currentLevel += "................................................................................................................................";
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
	currentLevel += "____%...dddddc***___________#--#___________%%%%..n.Z.dddd%%%%%%____________%%%%%ddd...Z.....%%%%%%%%____________________________";
	currentLevel += "_____%dbddddc,,s**oo*_______#--#_______________%%%%%%%%%%_______________________%%%%%%%%%%%%____________________________________";
	currentLevel += "*_____%%%ddc,,Ss****ooo***__#--#____________________________________*_____________________________________*_________**________**";
	currentLevel += "**_______%%*ooo***ss***oo***#--#*___**______*______________________***_____**______________________________**________***_____**_";
	currentLevel += "******____***ooo*ssssssss***#--#*****_____**_____________**_____************_________**_______*_____**_____******_********_*****";
	currentLevel += "**************ssssssssssssoo#--#*******_********_*******************************__********_**************_********_*************";
	currentLevel += "sssss*****oo*sssssssssssss*o#--#**ss*****************************sssssssss**********************************ssssss*sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssss**#--#**ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssss**#DD#**ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	
	
}

void Levels::CreateLevelThree()
{
	currentLevel = "";
	bossChar = L'K';
	spawnChar = L'-';
	cutsceneID = 0;
	currentSong = songList[1];
	currentBossSong = bossSongList[0];
	currentTileTxr = tileTextures[0];
	SetCurrentBackground(1);
	startCutscene = false;

	currentLevelWidth = 128;
	currentevelHeight = 22;
	miscChar = L'.';

	currentLevel += "............................................................###..........................###..................................##";
	currentLevel += "...........................................................#x#x#........................#x#x#..................................+";
	currentLevel += "..........................................................#x#x#x#......................#x#x#x#.................................+";
	currentLevel += "###xx###.................................................#########B...................#########..............................#x#";
	currentLevel += "#####x##x.................................................--yy---=.B..................=--y----................................#x";
	currentLevel += "#x###xxx##................................................---.---=.B..................=---.y--................................##";
	currentLevel += "##xxx####xx...............................................--.C.y-=.B..................=--.Z.y-................................#x";
	currentLevel += "####xx####x..............................................#########B...................#########..............................#x#";
	currentLevel += "######xx###..............................................#x#x#x#x#....................#x#x#x#x#...............................#x";
	currentLevel += "s---yyyy---..............................................##x#x#x##....................##x#x#x##...............................##";
	currentLevel += "sS-yyy---yy...v..b...n...b.Z....v.......................##x#x#x#x#.........vK.........#x#x#x#x#...............................#x";
	currentLevel += "###########%%%%%%%%%%%%%%%%%%%%%%%%%%%..b................################%%%%%%################..............................#x#";
	currentLevel += "****__________________________________%%%%%..b...........#################____#################..............................##x";
	currentLevel += "***_______________________*________________%%%%....nZ....##**************_#*_*_**************##..............................#x#";
	currentLevel += "**_**_________**__________**________*__________%%%%%%%%%%##*************_***_*#**************##..............................##x";
	currentLevel += "***___*_____****____*____*________**______________________***ssssssssss******_***sssssssss***##.............................##x#";
	currentLevel += "s******_***********__****************_____**_________*___***ssssssssssssssss****sssssssssss**##.............................#x#x";
	currentLevel += "ss***********************************_****__*____*__*__****ssssssssssssssssssssssssssssssss**##.............................##x#";
	currentLevel += "ssssssssssssssssssssssssssssssssssss************_*********sssssssssssssssssssssssssssssssss**###............................#x#x";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssss***************sssssssssssssssssssssssssssssssssss***##..........................##x#x#";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**###....b...n...Z.v....b....##x#x#x";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**####%%%%%%%%%%%%%%%%%%%%%%########";
	

}

void Levels::CreateLevelFour()
{
	currentLevel = "";
	bossChar = L'E';
	spawnChar = L'-';
	cutsceneID = -1;
	currentSong = songList[2];
	currentBossSong = bossSongList[1];
	currentTileTxr = tileTextures[0];
	startCutscene = false;
	SetCurrentBackground(2);
	currentLevelWidth = 128;
	currentevelHeight = 64;
	miscChar = L'-';

	currentLevel += "............####xxx##########xxxx######xxx#x########xxxx###########xxxx##xxxx............xx#.................xxxxxx#...........#";
	currentLevel += "............##xxx##########xxx###########xx########xx################xxx###xxx..........x#xx#...............xxxx####...........x";
	currentLevel += "............#xx----....y---....----....----....----....----....--------xx##--yy.........yy-yy..............yyyy--###...........x";
	currentLevel += "............xx#----....-yy-....----....----....----....----....---------#x-----VBy....yy-y--yy..........yyyy---y-###...........x";
	currentLevel += "............###----....--yy....----....----....----....----....---------#x-----VByy..yyy---y--yy......yyy--yy----#x#...........#";
	currentLevel += "............###----....y---....----....----....---y....----....-------yy##-----VB-yyy--yy----y--y...yy-y---------#xx...........#";
	currentLevel += "............-------....-yy-....----....----....--yy....----....-----yyy-##y----VB-yy-----------y-yyy---yyy-------##x...........#";
	currentLevel += "............-------....--yy....----....----....--yy....----....----yy----=-yy--VB-yyy----------.--yy-----yy-------=--.-.-.-.-.-+";
	currentLevel += "..........#.-C------..----yy..------..------..--yyyy..------..----yyyy---=-yyy-VB---yy--------.E.--yy---yy--------=------------+";
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
	currentLevel += "...........#xssssssssssssx#-------#xx######xxx######---yy---y------y------------yy.............yy----------.-----#xx#...........";
	currentLevel += "...........xxssssssssss#xx#--------##xx#####xxxx###--yy-yy-y----y--y-y--------yyy-y...yn.K...y.y----------.Z.v---xxx#...........";
	currentLevel += "...........#x#ssssxxx##x##-----------yyy-----yy-------yy-y-y-----yy.y--y#########xxxxxxxxxxxxxxxxx############xxxxx##...........";
	currentLevel += "............#x##xx###xx#y--------------yyy----yy-------yy.y-------y.y-y-#####x##x##xxxxxxxxxx##x###x########xxxx####............";
	currentLevel += "............##xx###--yyy----------------yy-----y--------y..y----yy...y--x##xsssssssssssssssssssssssssssssssssssss###............";
	currentLevel += "............#xx------yy------------------yy-b-y--------y...y---y-y###y--xx#sssssssssssssssssssssssssssssssssssssss##............";
	currentLevel += "............xx#-----yy--------.---###################-yy###y------xx--y-xx#sssssssssssssssssssssssssssssssssssssss##............";
	currentLevel += "...........xx##----y---------.C.--###################yy--xx-y---------yy#xxsssssssssssssssssssssssssssssssssssssss#xx..........."; 
	currentLevel += "...........x###--yyy-------##########sssssssssssss###-------------------##xsssssssssssssss######xxxx###########sssxx#..........."; 
	currentLevel += "...........####yy----------#########sssssssssssssss##---y---------------#xx#ssssssss#xxx##########xxxxx##########xxx#...........";
	currentLevel += "...........###xyy--------############################----y----y----yyy--xx########xxxx#####-----yyyy----------###xx##...........";
	currentLevel += "............##x-yy--y-###############################----yy--y.y-yy--yy-x######xxxx##---------yyy--.-------------x##............";
	currentLevel += "............##x--yyy--####y-----yyy------------------------yyy.yy------------yyyy-----------yyy---...-------------##............";
	currentLevel += "............#x#-yy-----.yy-----yy---------.-----------------y..y-y---------yyyy------------yy--.---.----------------............";
	currentLevel += "............#x#yy-----.Z.yy---yyy--------.K.----------------y...y--------yyyy-------------yyyy.K.-------------------............";
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
	currentLevel += "............###--...-----------yy...yyy---------------y.--...y.y...--.-----------...---------------.----.-----------.....xx.....";
	currentLevel += "............##x--...------------y...y-----------------..--...yyy...--..----------...-------------------.K.----------.....yy.....";
	currentLevel += "............#xx--...-------------...y-----------------..--...-yy...--..---y------...---------####xxxx#######x##xx###....-yy.....";
	currentLevel += "............#xx--...-------------...-------------------.--...--y...--.--yy-------...--------y##xxxx#########xxx##x##..--yy......";
	currentLevel += "...........#xx#--y.yy------------y.y---.------------------...---...---yyy------.--.-------yyy#xxsssssssssssssssss###--y-y.......";
	currentLevel += "...........#x##-v-yyyyy---------yyy---.Z.----v-------------.--.--.--yyy-------.Z.-v-----yyy--##sssssssssssssssssss##-y-y........";
	currentLevel += "...........#######xxxyy----#####xxx#####xxxx###xx###---------.K.----yyyy########xxx####yy----##sssssssssssssssssssx#yyy.........";
	currentLevel += "...........#x#####xx--yy--#xx######xxxxx#####xxx#######xxxx#########xxx#x########xxxx##y-y---##sssssssssssssssssss#xyy..........";
	currentLevel += "............xx#####s---yy#x#sssssssssssssssssssssss######xxxx#########xx#sssssssssss###---yy-##sssssssssssssssssssxxy...........";
	currentLevel += "............#xxx###sS---###ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssx#-----y##sssssssssssssssssss#x............";
	currentLevel += "............##xxx#########sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssxx------##sssssssssssssssssss##............";
	currentLevel += "............###xxxxx#####ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#xDDDDDD##sssssssssssssssssss##DDDDDDDDDDDD";

	
}

void Levels::CreateLevelFive()
{

	currentLevel = "";
	spawnChar = L'.';
	cutsceneID = 2;
	currentSong = songList[2];
	currentTileTxr = tileTextures[0];
	startCutscene = true;
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
	currentLevel += "s-----....----....----....----....----....----....-----------+";
	currentLevel += "s------..------..------S.------..------..------..------------+";
	currentLevel += "##############################################################";
	currentLevel += "##############################################################";
	currentLevel += "###ssssssssssssssssssssssssssssssssssssssssssssssssssssssss###";
	currentLevel += "#ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

	
}




void Levels::CreateLevelSix() 
{
	currentLevel = "";

	currentTileTxr = tileTextures[1];
	currentSong = songList[1];
	currentBossSong = bossSongList[0];
	SetCurrentBackground(3);
	currentLevelWidth = 128;
	currentevelHeight = 60;
	cutsceneID = 0;
	spawnChar = L'-';
	startCutscene = false;
	bossChar = L'p';
	miscChar = L'.';
	darkMode = false;

	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss#########################################sssssssssssssssssssssssssssssssssssss#############sssssssss";
	currentLevel += "sssssssssssssssssssssssssss###########################################sssssssssssssssssssssssssssssssssss###############ssssssss";
	currentLevel += "sssssssssssssssssssssssssss###--------......------L#L-------...----###ssssssssssss###########################-------#####sssssss";
	currentLevel += "sss##########################L-------..Z..--------L#L------.Z.-----###sssssssss###########################----------..####ssssss";
	currentLevel += "#############################L----############----L#L----######----###ssssssss#####--------------------------------..---###sssss";
	currentLevel += "######---..----------.-----##L----L##########L----L#L----L####L----###sssssss###---.----------...-----------------..----###sssss";
	currentLevel += "#####-----..-------..------##L----L##ssssss##L----L#L----L####L----####sssss###---.G.--------..C..---------------..-----###sssss";
	currentLevel += "#####------.------.--------l#L----L##ssssss##L----###----L####L----###########-----.--#####################-----...-----L##sssss";
	currentLevel += "#####------..----..--------l#L----L##ssssss##L----..-----L####L-----.########---------####################L----.....----L##sssss";
	currentLevel += "#####------HH----HH--------##L----L##ssssss##L---..------L####L---.......-------------###ssssssssssssss###L----HHHHH----L##sssss";
	currentLevel += "####s------##----##--------###----L##ssssss##L-....-...--L####L--.........------------##ssssssssssssssss##L.---#####----L##sssss";
	currentLevel += "####sS-----##----##---------------L##ssssss##L..........-L####L.............----------##ssssssssssssssss##L..-----------L##sssss";
	currentLevel += "#####################-------------L##ssssss##L...........L####L............Z.---------##ssssssssssssssss##L..-----------L##sssss";
	currentLevel += "#####################################ssssss###HHHHHHHHHHH######HHHHHHHH#######-------.##ssssssssssssssss##L...----------L##sssss";
	currentLevel += "#####sssssssssssssss#################ssssss###################################-----...##ssssssssssssssss##L....---------L##sssss";
	currentLevel += "###sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##---.....##ssssssssssssssss###HHHH..---#######sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##-.......##ssssssssssssssss#######--.-----####sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##........##ssssssssssssssss####-----.....--l##sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##HHHHHHHH##ssssssssssssssss##L------HHH...-###sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss############ssssssssssssssss##L------###HH..###sssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss##L-------.###HH###sssss";
	currentLevel += "sssssssss############################ssssssssssssssssssss################################sssssssssssssss##L------....######sssss";
	currentLevel += "sssss####################################ssssssssssss#########################################ssssssssss##L----.....---####sssss";
	currentLevel += "sss#######-------..................-######################-.......---------..........---#######sssssssss##L-......------l##sssss";
	currentLevel += "sss##-----------.......................-##############-............-------................---##sssssssss##L......------.###sssss";
	currentLevel += "sss##----..-----.........................-----------...............-------..................-l##ss#########HHHHHH------.###sssss";
	currentLevel += "sss##---....---............................--------....G............-----....................####################----..-###sssss";
	currentLevel += "sss##-......---............................----C---..............G..-----....................-#####-----------------..--###sssss";
	currentLevel += "sss##.......---............................########.................-----..G..................---------------------.Z---####ssss";
	currentLevel += "sss#r.......---............................l######r.................-----............G.........----------#####################ss";
	currentLevel += "sss##.......---..................G.........########.................-----.....................------##########################ss";
	currentLevel += "sss##......-----...........................########.................-----....................-###########sssssssssssssssssssssss";
	currentLevel += "sss##......-----...........................########................-------...................-l#####ssssssssssssssssssssssssssss";	
	currentLevel += "sss##.....-------..G.......................########................-------...................-###sssssssssssssssssssssssssssssss";
	currentLevel += "sss##.....##---##..........................########...............---------...................##ssssssssssssssssssssssssssssssss";
	currentLevel += "sss##DDDDD##---##DDDDDDDDDDDDDDDDDDDDDDDDDD########DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD##ssssssssssssssssssssssssssssssss";
	currentLevel += "sss#########---#############################################################################################ssssssssssssssssssss";
	currentLevel += "sss#########---##########################################################################################################sssssss";
	currentLevel += "ssssssssss##---##sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss#######################################sssss";
	currentLevel += "ssssssssss##---##sssssssssssssssssssssssssssssssssssssssssssssss#################################-.............=..-#########ssss";
	currentLevel += "ssssssssss##---##ssssssssssssssssssssssssssssssss####################################-..B......................=........-####sss";
	currentLevel += "ssssssssss##---##ssssssssssssssssssssss##########################--------...........=...B......................=..........-###ss";
	currentLevel += "ssssssssss##---##ssssssssssssssss#################-...........----------............=...B......................=...........-##ss";
	currentLevel += "ssssssssss##---##ssssssssssss###########-----.................----------............=...B......................=............###s";
	currentLevel += "ssssssssss##---##sssssssss########----------...................--------.............=...B......................=............###s";
	currentLevel += "ssssssssss##---##sssssss######-....---------...................--------.............=...B......................=............-##s";
	currentLevel += "ssssssssss##---##ssssss####-........-------....................--------.............=...B......................=.............##s";
	currentLevel += "ssssssssss##---##sssss###-..........-------....................--------.............=...B......................=.............##s";
	currentLevel += "ssssssssss##---##ssss###-...........-------....................--------.............=...B......................=.............##s";
	currentLevel += "ssssssssss##---##sss###-............-------....................--------............G=...B.........p............=.............##s";
	currentLevel += "ssssssssss##---#######-.............-------....................--------.............=...####################...=.............##s";
	currentLevel += "ssssssssss##---#######..............-------....................--------...G.........=...####################...=.............###";
	currentLevel += "ssssssssss##----------..............-------................G...--------.............=....##ssssssssssssss##....=....G........###";
	currentLevel += "ssssssssss##----------..............-------..G................----------............=.....##ssssssssssss##.....=.............-+#";
	currentLevel += "ssssssssss##----------...........G.---------..................----------............=.....##ssssssssssss##.....=.............-+#";
	currentLevel += "ssssssssss##############..........-----------................------------...........=.....##ssssssssssss##.....=..........######";
	currentLevel += "ssssssssss##############DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD##ssssssssssss##DDDDDDDDDDDDDDDD######";
	


}

void Levels::CreateLevelSeven()
{
	currentLevel = "";

	currentTileTxr = tileTextures[1];
	currentSong = songList[1];
	currentBossSong = bossSongList[0];
	startCutscene = true;
	bossChar = L'p';
	SetCurrentBackground(4);
	currentLevelWidth = 274;
	currentevelHeight = 26;
	cutsceneID = 3;
	spawnChar = L'}';
	miscChar = L'.';

	darkMode = false;

	currentLevel += ".....................................................................................................................................................dd______________________dddddddddd..........................ddddddddd______________ddddddddddddddd_______________ddd........+";
	currentLevel += ".......................................................................................................................................................dd_______________dddddddd......................................dddddd_________ddddd....dddddddddddd_________dd............+";
	currentLevel += ".........................................................................................................................................................d__________dddddd...............................................dddd_______ddd.........dddd......d_______d..............+";
	currentLevel += ".........................................................................................................................................................d_________ddd.....................................................ddd______dB...........dd.......dd______...............+";
	currentLevel += "..........................................................................................................................................................________dd...............G.........................................d_____d.B...........d.........d_____d............}}}+";
	currentLevel += ".............................................................................................................................}}}}}}}}v}.C.}}}n}}}}........________d............................................................____..B......................_____......G......%%%%";
	currentLevel += ".............................................................................................................................%%%%%%%%%%%%%%%%%%%%%.........______d.............................................................____..B......................_____.............____";
	currentLevel += ".............................................................................................................................L____________________%........dddddd.........G.................}}}b}}}}...........................____..B......................=___d.............d___";
	currentLevel += "................................................................................................}}}}}}}}}n}K}}}}}}}}}}......dL_____________________.........dddd.........................}}}%%%%%%%%[...................[.Z]...____..B......................=dddd.............d___";
	currentLevel += "........................................................G.......................................%%%%%%%%%%%%%%%%%%%%%%......dL_____*_______*_______H..........ddd........................%%%________%...................%%%%...____..B......................=.dd..............dd__";
	currentLevel += "{.......................................G..................................G...................._____________________L.....ddL____**_____**________%..........G....................HHHHHH____________...}}v}}...........____...dddd..B......................=..d...............d__";
	currentLevel += "%..........................]...................{.{............................}}}v}}............____________________*Ld....ddL_*******_******_**____.........................HHHHHH%%%%%%_______*____...%%%%%...........___d...ddd...B......................=..................d__";
	currentLevel += "_[........................###.................####............................%%%%%%............______*________*___**Ld...dddL*******************___HHHH.............HHHHHHHH%%%%%%___________**_____..._____......}}}..___d....dd...B......................=..................___";
	currentLevel += "_%........................##L.....[...........####.................G....D.....L_____............d______*____*___*_***Lddd.dddL***ssss***ssss*****___%%%%HHHHHHHHHHHHH%%%%%%%%___________*___****_____...d___d......%%%..d__..........B}}}}}}}}n}p}}}}}}}}}..=.................D___";
	currentLevel += "#_........................##L....###..........####.....................D*.....L_____............d__*******_**********LdddddddL**sssssssssssssss**_______%%%%%%%%%%%%%_______________*____********_*__....d__.......___...__H...HHHH..B%%%%%%%%%%%%%%%%%%%%..=.................%___";
	currentLevel += "##........................##L....L##..........####.........D...........**D....L_____%............dd_******************dddddddL**sssssssssssssss**___*__________________________*___**********ss***___HHH..__H......___..H___.HH%%%%HHH___________________...=..............DDD____";
	currentLevel += "s.........................##L....L##..........####.........*..........D***....L______............ddd,,,,************,ddddddddL**sssssssssssssss*****__*______________*___*___*************ssssss**___%%%HH___HHHHHH___HH____H%%____%%%___________________DDDDDDDDDDDDDDDDDD%%%____";
	currentLevel += "sS}}}}}...................###....L###.........####........D*.........D****D...L______}}}}........ddd,,,,,,,,,,,,,,,,,,dddddddL**sssssssssssssss*********_____**_______**************ssssssssssss**______%%___%%%%%%___%%____%______________*___**________%%%%%%%%%%%%%%%%%%______*";
	currentLevel += "####%%%}}}v}}}}}..........---....L###.{.n..{.{####........**D........******DDD*______%%%%}}b}}}Z}dddd,,,,,,,,,,,,,,,,,,ddddddL**sssssssssssssssssss*******_********_**********ssssssssssssssssss***_________________*____*__________________****____**__________________________**";
	currentLevel += "####___%%%%%%%%%}}}}b}}}}}---}}}}L###*************D......D***D......D**ss********________%%%%%%%%%__***,,,,,,,,,,,,,,,,,,ddd****sssssssssssssssssssssss****************ssssssssssssssssssssssssss****______**______**___***____***_______*_**********________________________*_***";
	currentLevel += "*_______________%%%%%%%%%%%%%%%%%******************DD..DD*****DD..DD***sss**********_______________*****************************ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*****_*******_***************************************_____**_______**_______***s";
	currentLevel += "**____**___*____________________*****ssssssssss******DD****s****DD****ssssssssss*****_*__*________*****************************sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**************************************ssssssssss*****__**_________**___*****ss";
	currentLevel += "***_*****_****______*___**_____***ssssssssssssss**********sss********ssssssssssssss******____**___**ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*********_***************sss";
	currentLevel += "s***************_***********_****ssssssssssssssss*******sssssss****sssssssssssssssss*******_********ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss********************ssssss";
	currentLevel += "sssssssssssss*******************ssssssssssssssssssssssssssssssssssssssssssssssssssssssss***********sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
}

void Levels::CreateLevelEight()
{
	currentLevel = "";
	bossChar = L'N';
	spawnChar = L'.';
	currentTileTxr = tileTextures[2];
	currentSong = songList[1];
	currentBossSong = bossSongList[1];
	SetCurrentBackground(4);
	currentLevelWidth = 80;
	currentevelHeight = 65;
	cutsceneID = -2;
	startCutscene = false;
	darkMode = false;
	miscChar = L':';

	currentLevel += "....wwwsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssswww....";
	currentLevel += "...wwwsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssswww...";
	currentLevel += "..wwwsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssswww..";
	currentLevel += ".wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.";
	currentLevel += "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
	currentLevel += "...##wwwwwwww[::::::::::::::::::::::::::::::::::::::::::::::::::::[wwwwwwww##..+";
	currentLevel += "...##wwwww::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::wwwww##..+";
	currentLevel += "...##www:::::::::::::::::::::::::::::::::::::::n::::::::::::::::::::::::www##..+";
	currentLevel += "...##ww::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::ww##..+";
	currentLevel += "...##w::::::::::::::::::::::::{:::::::::::::::::::::::::::::::::::::::::::w##..+";
	currentLevel += "..]##w::::n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::n:::::w##].+";
	currentLevel += "..###::::::::::::::::v:v:v:v:::::::v::b:N::v:::::::v:v:v:v:::::::::::::::::###.+";
	currentLevel += "..##L::::***:::----w*********wHHHw***********wHHHw*********w----:::***:::::L##.+";
	currentLevel += "..##L::::www:::HHHHwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwHHHH:::www:::::L##.+";
	currentLevel += "..##L::::::::::wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww:::::::::::L##.+";
	currentLevel += "..##L::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::L##.+";
	currentLevel += "..##L:::{:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Zv:L##.+";
	currentLevel += "..##L:::::::::::::::::n::::::::::::::::::::::::::::::::::::::::::::::*****w###.+";
	currentLevel += "..##L:::::::::::::::::::::::::::::::::::::::::::::::::::::::::..::::*wwwwww##..+";
	currentLevel += "..##L::v:v:v:v::vpv:::b::::v:v:v::::b:::::::::::::::::::::::::.]:::*ww::::[##..+";
	currentLevel += "..###w***********************************:::::::::::::::::::::::::*ww::::::##..+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww*:::::::::::::::::{:::::*ww::::::###..+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwwwwww[:::::::ww*::::::::::n::::::::::*ww:::::::##...+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwww-:::::::::::ww*:::::::::::::::::::*ww::::::::##...+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwww-:::::::::::::::::::::::::}::::::::::::::::::::##...+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwww-::::::::::::::::::::v:v:::b:::v:v:::::::::U::::##...+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwww::::::::::::::::::::***************w::::::::::::##...+";
	currentLevel += "...##D,y--y,--yy,wwwwwwwww:::{:::::::::::::::*wwwwwwwwwwwwwwww::::::::::::##]..+";
	currentLevel += "...##D,-yyy,-yy-,wwwwwwwww::::::::::::::::::*ww[::::::::::::::::::::::::::###..+";
	currentLevel += "...##D,--y-,--G-,--y--yy-G:::::::::::::::::*ww::::::::::::::::::::v::::::::##..+";
	currentLevel += "...##D,-yy-,y--www--yy-y-,::::::::::..::::*ww::::::::::::::::::::www:::::::##..+";
	currentLevel += "...##D,y-y-,y--lwwHHHHHHHHww::::::::.]:::*ww::::::::::::::::::::::::::{::::##..+";
	currentLevel += "..]##D,-y-y,yy-lwwwwwwwwwwww::::::::::::*ww::::::::::::::::::::::::::::::::##..+";
	currentLevel += "..###D,---y,y-ylwwwwwwwwwwww:::::::::::*ww:::::::::::::{:::::::::::::::::v:##..+";
	currentLevel += "..###D,yyy-,-y-lwwwwwwwwwwww::::::::::*ww::::::::::::::::::::::n::::::::www##..+";
	currentLevel += "..###D,-y--,y-ywwwwwwwwwwww::::::::::*ww::::::::::::::::::::::::::::::::::[##..+";
	currentLevel += "..###D,-y-y,y--Lwwwwwwwwww:::::::::::::::::::::::::n:::::::::::::::::::::::##..+";
	currentLevel += "..###DG,,,,,,,,Lwwwwwwwwww:::::::::::::::::::::::::::::::::v:::b:::v:::}:::##..+";
	currentLevel += "..###D,y---,--ywwwwwwwwwww:::v:}:::::::U:::::::::::::::::w****************w##..+";
	currentLevel += "..###D,y--y,-y-lwwwwwwwwwww*****w:::v:::v:::v:::::::U:::::wwwwwwwwwwwwwwwww##..+";
	currentLevel += "..###D,yy-y,yy-lwwwwwwwwwwwwwwwwww**************:::::::::::::::::::::-wwwww##..+";
	currentLevel += "..###D,y-yy,y-ylwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww*::::::::::::::::::::::-www###.+";
	currentLevel += "..###D,-y--,-y-wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww*::::::::::::::::::::::-ww###.+";
	currentLevel += "..###L,-y-y,-y-ywwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww*::::{:::::::::::::::::[w###.+";
	currentLevel += "..###L,,,,G,,,,,,,,,,wwwwwwwwwwwwwwwwwwwwwwwwwwwwww*:::::::::::::::n::::::w###.+";
	currentLevel += "...##L,y--y,-yyy,--yy,--y-,y--,-y-y,ywwwwwwwwwwwwwww*:::::::::::::::::::::-###.+";
	currentLevel += "...##w,y-y-,y-y-,-yy-,y-yy,---,--y-,y--y,---wwwwwwwww*:::::::::::::::::::::###.+";
	currentLevel += "...##-,-yy-,yy--,yyy-,-y-y,---G-yy-,--y-,y--y,wwwwwwww*::b::::v::::::::::::###.+";
	currentLevel += "...##-,-y-y,-y--,yy-y,----,y--,y-yy,-yyy,-yG-,--wwwwwww**********w:::::{:::###.+";
	currentLevel += "...##H,-y--,--yy,y--y,--y-,yy-,--y-,y-y-,--y-,y-y-wwwwwwwwwwwwwwwwww:::::::###.+";
	currentLevel += "...##wHHHH-,--yy,----,y-HHHHHHHHHHHHH--y,-yy-,-y-y,::ww[:::::::::ww::::::::##..+";
	currentLevel += "...##wwwwwHHHHHHHHHHHHHHwwwwwwwwwwwwwHHHHHHH-,-yy-G::::::::::::::::::G:::::##..+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwHH--y-,::::::::::::::::::::::}:##..+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww***w:::::::::n::::::::w****w##..+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww::::{:::::::::::::wwwwww##..+";
	currentLevel += "...##wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwB:::::::::::::::::wwwwww##..+";
	currentLevel += "...##ww[:::::::::::::::::::::::::::::::::::::::::::VB:::::::::::::{::=::::w##..+";
	currentLevel += "...##w::::::::::::{::::::::::::::::::::::::::::::::VB::::::::::::::::=::::w##..+";
	currentLevel += "....:::::::::::::::::::::::n::::::::}::::::::::::::VB::v:v::b::v:::::=::{:::...+";
	currentLevel += "S...::::::::v:v:::b:::v:v:::::v::v::b::v:v::C:::}::VB:w**********w:::=::::::...+";
	currentLevel += "%%%wwww**********************************************wwwwwwwwwwwwwwwwwwwwwwww%%%";
	currentLevel += "___wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww___";
	currentLevel += "___ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss___";
	currentLevel += "__ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss__";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

}

void Levels::CreateLevelNine()
{
	currentLevel = "";
	spawnChar = L'}';
	currentTileTxr = tileTextures[1];
	currentSong = songList[1];
	currentBossSong = bossSongList[1];
	SetCurrentBackground(4);
	currentLevelWidth = 270;
	currentevelHeight = 22;
	bossChar = L'P';
	cutsceneID = -3;
	startCutscene = false;
	darkMode = false;
	miscChar = L'-';

	currentLevel += ".....................................%____******sssssssssssssssssssssssssssssssssssssssssssss***************#######################ssssssssssss#################################ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "...................................%%___********sssssssssssssssssssssssssssssssssssssssssssss************###########################ssssssssss###--------------------###############ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += ".................................%%___**,,,,,,***ssssssssssssssssssssssssssssssssssssssss********,,,,,----------------------------####sssssss###-------------------------------##########sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "................................%__,,,,,,,,,,,,***sssssssssssssssssssssssssssssssssssssss*****,,,,,,-----------------C--------------##sssssss##L-----------------------------------########sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "...............................%_,,,,,,,,,,,,,,,**sssssssssssssssssssssssssssssss*********,,,,,,,,,,-G-------################-------###ssssss##L-----HHHHHHH-----------------------------####ssssssssssssssssssssssssssssssssssssssssss#############ssssssssssssssssssssssssss";
	currentLevel += "..............................._,,,,,,,,,,,,,,,,**ssssssssssssssssss******************,,,,,,,,,,,,,,------###################--------##ssssss##L----H#######H------------------------------###sssssssssssssssssssssssssssssssssssss#####################ssssssssssssssssssssss";
	currentLevel += "..............................%_,,,,,,,,,,,,,,,,**ssssssssssssssss****************,,,,,,,,,,,,,,,,,,,,------####ssssssssss##r--------##ssssss##L----L########H-------------------------------##sssssssssssssssssssssssssssssssss########-----....--########sssssssssssssssssss";
	currentLevel += ".............................._L,,,,,,,,,,,,,,,,**sssssssssssssss**r,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,-----###ssssssssss##--------##ssssss##L----L##ssss###-------------------------------###ssssssssssssssssssssssssssssss######-------.......-----######sssssssssssssssss";
	currentLevel += ".............................._L,,,,,,,,,,,,,,,,**sssssssssssss**r,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,----###sssssssss##--------##ssssss##L----L##sssss##------------G-------------------####sssssssssssssssssssssssssss####---.....---.......-------####sssssssssssssss*";
	currentLevel += ".............................._L,,,%r,,,,,,,,,,,**sssssssssss***r,,,,,,G,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,----###ssssssss##--------###ssss###L----L##sssss##----------------------------------######ssssssssssssssssssssss###V---........--......--...----###ssssssssssssss*";
	currentLevel += ".............................._L,,,Lr,,,,,,,,,,,**sssssssss****r,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,--L##ssssssss#r--------##########L----L##sssss##------------HHHHHHH----------------#########ssssssssssssssssss##--V---..............-......----##############***";
	currentLevel += ".............................._L,,,Lr,,,,,,,,,,,***sssssss***r,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,G,,,,L##ssssssss##---------##########----L##sssss##H---------HH#######H-------------------########ssssssssssssss###--VB.-......................---############*****";
	currentLevel += "..............................##,,,Lr,,,,,,,,,,,,**ssssss**r,,,,,,,,,,,,HHHH,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,L##ssssssss##-----------------------L##sssss###HHHHHHHHH##########-----------------------######ssssssssssss##---VB........................---=-----------,,,,+";
	currentLevel += ".................................,,Lr,,,,,,,,,,,,**********,,,,,,,,,,,,,****HH,,,,,,G,,,,,,,,,,,,,,,,,,,,,,,,,,,**#ssssssss##H-------------------G--L##ssssss#############sss##L----------------------------#################----VB.....................-.---=------------,,,+";
	currentLevel += "S}}}}}...................}}}}Z}}}}}L_H,,,,,,,,,,,,********,,,,,,,G,,,,,,******H,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssss###----------------------L##sssssss###########ssss##L------------------------------###############----VB-................-...-.---#############****";
	currentLevel += "%%%%%%}}}Z}}v}}K}}}}n}}}}%%%%%%#####**H,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,HH**s****H,,,,,,,,,,,,,,,,G,,,,,,,,,,,,,,,**ssssssssss##HH--------------------###ssssssssssssssssssssss##L-------------------------------------------##---VB--................--.--..--###############**";
	currentLevel += "______%%%%%%%%%%%%%%%%%%%____________**HH,,,,,,,,,,,,,,,,,,,,,,,,,,,,,****sss***HHH,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssssss###HHHHHHHHHHHHHHHHHHHH###ssssssssssssssssssssss##L-------------------------------------------==---VB---................--------##ssssssssssssss*";
	currentLevel += "__*_________________________*___*____****HH,,,,,,,,,,G,,,,,,,,,,,,,HHH***sssss*****HHHH,,,,,,,,,,,,,,,,,,,HHHHHH**ssssssssssss#########################ssssssssssssssssssssss###-----------------------------------C-------==--VB-------...--P....-----------##sssssssssssssss";
	currentLevel += "******_______*______*____******************HHH,,,,,,,,,,,,,,,,,,,HH*****sssssss********HHHHHHHHHHHHHHHHHHH********sssssssssssss#######################sssssssssssssssssssssss###---------------------------####################################################sssssssssssssss";
	currentLevel += "**s*************************s***s*************HHHHHHHH,,,,,,,,,HH******sssssssssss*******************************ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss###-----------------##############################################################sssssssssssssss";
	currentLevel += "sssss********s******s*****ssssssssssssssss************HHHHHHHHH*****ssssssssssssssssss*********************ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss###HHHHHHHHHHHHHHHHH###########ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssss******************sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss######################sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

}


void Levels::CreateLevelTen() 
{

	currentLevel = "";

	currentTileTxr = tileTextures[0];
	currentSong = songList[0];
	SetCurrentBackground(0);
	currentLevelWidth = 128;
	currentevelHeight = 58;
	cutsceneID = 0;
	spawnChar = L'.';

	startCutscene = false;
	darkMode = true;

	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**********ssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssss*********sssssssssssssssssssssssssssssssssssssssssssssssssssssssss****************ssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*************ssssssssssssssssssssssssssssssssssssssssssssssssssssss****,,,,,,,,*****ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss****,,,,,,,*******s***************************************************,,,,,,,,,,,,,,+ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss***,,,,,,,,,,********************************************************,,,,,,,,,,,,,,,+ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,,,,,,,,,***,,,,,,,,,,,,,..,,,,,,,,..,,,,,,,,,,,,,,...,,,,,,,,,,,,,,,********ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,,,,,,,,,,,,,,,,,,,,,,,..W,,,,,,,,.W,,,,,,,.W.,,,,,,W,,,,,,,,,,,,,,,,********ssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,****************************************************************,,,.***sssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L***************************************************************,,..**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L***sssssssssssssssssssssssssssssssssssssssssssssssssssssssss***,...**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**L,,,,,,L**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssss***L,,,,,,***sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssss********,,,,,,***sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssss*******..,,,,,,,***sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss****,,,,,...,,,,,***sssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**....**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss***.,,,,,,.G..,,***ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**,...**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**...,,,,,,..******sssssssssssssssssssssssssssssssssssssssss***************ssss**,...**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**.....,,,,,,..*****sssssssssssssssssssssssssssssssssssss************************,..,**ssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**.......,,,,,,,,****ssssssssssssssssssssssssss**************,........,,,,*******,,.,***sssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**........,,,,,,,,****************************************,,,..........,,,,,,***,,,,,*****sssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**,.........,,,,,,,,****************************,,,,,,,,,,,,,..........,,,,,,,,,,,,,,.******sssssssssssssssss";
	currentLevel += "sssssssssssssssssss***,..........,,,,,,,,,,,,,,,,............,,,,,,,,,,,,,,,,,,,.........,,,,,,,,,,,,,,...,,****ssssssssssssssss";
	currentLevel += "sssssssssssssssssss****,.b....K.b..,,,,,v,,,,,,,.....Z........,,,n,,,,,,,,,,,,,,,,......,,,,,,,,,,,,,,...,,,,,***sssssssssssssss";
	currentLevel += "ssssssssssssssssssss*************************************************,,,,,,,,,,,**,,,,,,***,,,,,,,,,,...,,,,,,,***ssssssssssssss";
	currentLevel += "ssssssssssssssssssssss***********************************************,,,,,,,,,,,**,,,,,,**L,,,,,,,,,..C..,,,,,,***ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss***,,,,**,,,,,**,,,,,,**L,,,,,************,,,L**ssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**,,,,**,,,,,**,,,,,,**L,,,,.L**********L,,,L**ssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**,,,,**,,,,,**,,,,,,**L,,,..L***ssss***L,,,L**ssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**,,,,**,,,,,**,,,,,,**L,,..,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**,,,,**,,,,,**,,,,,,**L,..,,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssss******************************ssssssss**,,,,**,,,,,**,,,,,,**L..,,,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss********************************sssssss**,,,,**,,,,,**,,,,,.**L.,,,,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss***,,,,,,,............,,,,,,,,***ssssss**,,,,**,,,,,**,,,,..**L,,,,,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L,,,,,,..............,,,,,,,,**ssssss**,,,,**,,,,,**,,,..,**L,,,,,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L,,,,,....b...K...b...,,,,,,,**ssssss**,,,,**,,,,,**,,..,,***,,,,,L**ssssss**L,,,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L,,,********************,,,***sssssss**,,,,,,,,,,,,,,..,,,,,,,,,,,L**ssssss**L,.,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L,,,L*******************,,,**ssssssss**,,,,,,v,,,,,,.W.,,,,,,n,,,,L**ssssss***.G,L**ssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**L,,,L***sssssssssssss***,,,**ssssssss********************************ssssss***..,L**ssssssssssssss";
	currentLevel += "ssssssssssssssss**************L,,,L**sssssssssssssss**,,,**sssssssss******************************ssssss***,,,,***ssssssssssssss";
	currentLevel += "sssssssssssssss****************,,,L**sssssssssssssss**,,,********************************ssssssssssssss****,,,,***ssssssssssssss";
	currentLevel += "ssssssssssssss****,,,,,,,,,,,,,,,,L**sssssssssss******,,,*************************************************,,,,,***ssssssssssssss";
	currentLevel += "ssssssssssssss**,,,,,,,,,,,,,,,,,,L**ssssssssss***,,,,,,,,,,,,........................,,*****************,,,,,,***ssssssssssssss";
	currentLevel += "ssssssssssssssss,,,,,,,,,,,,,,,,,,L**ssssssssss**,,,,,,,,,,,,..........................,,**....,,,,,,,,,,,,,,,,***ssssssssssssss";
	currentLevel += "ssssssssssssssssS,,,,,v,,,,,n,,,,,L**ssssssssss**,,,,,v,,,,K....b............b......b..,,,,,W.,,,,,,,,,,,,,,n,,***ssssssssssssss";
	currentLevel += "ssssssssssssss***********************ssssssssss*******************************************************************ssssssssssssss";
	currentLevel += "ssssssssssssss***********************sssssssssss*****************************************************************sssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
}

void Levels::CreateLevelEleven()
{
	currentLevel = "";

	currentTileTxr = tileTextures[0];
	currentSong = songList[0];
	SetCurrentBackground(0);
	currentLevelWidth = 128;
	currentevelHeight = 58;
	cutsceneID = 0;
	spawnChar = L',';
	startCutscene = false;

	darkMode = true;
	
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssss**********sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*****************************************************ssssss****************************sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss******************************,,,,....***************ssssss****************************sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....,,,,,,,,,,,,,,**ssssss***************,,,,,,,,*****sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..U.,,,,,,,,,,,,,,,**ssssss**,,,,,,,,,,,,,,,,,,,,,,,+**sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.HHHH,,,,,,,,,,,,,,,**ssssss*L,,,,,,,,,,,,,,,,,,,,,,,+**sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,******************,,,***************************ssssss*L,,,,,,,,,,,,,,************sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,L****************L,,,L**************************ssssss*L,,,***********************sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,L*ssssssssssssss*L,,,L*sssssssssssssssssssssssssssssss*L,,,L***********ssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,L*ssssssssssssss*L,,,L*sssssssssssssssssssssssssssssss*L,,,L*ssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssss****************L,,,L*ssssssssssssss*L,,,L*sssssssssssssssssssssssssssssss*L,,,L*ssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssss*****************,,,L*ssssssssssssss*L,,,L***********sssssss**********ssss*L,,,L*ssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssss**,,,,,,,,,,,,,,,,,,L*ssssssssssssss*L,,,L*********************************L,,,L*ssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssss**,,,,,,U,,,,,,,,,,,L*ssssssssssssss*L,,,***,,,,....*********,,,,....*******,,,L*ssssssss*************sssssssssssss";
	currentLevel += "sssssssssssss**,,,,,,,,,,,,,,,,,,L*ssssssssssssss*L,,,,,,,,,......,,,...,,,,,......,,,,,,,,,L*ssssssss*************sssssssssssss";
	currentLevel += "sssssssssssss*****************,,,L*ssssssssssssss*L,,,,,,,,......,,...,,,,,,......,,,,,,,,,,L*ssssssss**,,,,,,,,,**sssssssssssss";
	currentLevel += "sssssssssssss****************L,,,L*ssssssssssssss**,,,,,,,,HHHH.,,.b.,,,,,,.HHHH.,,,,,,,,,,,**ssssssss*L,,,,,,,,,**sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,L*ssssssssssssss*********************************************ssssssss*L,,,,,,,,,**sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,L**********sssss*********************************************ssssssss*L,,,********sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,.,L***************************************************************sssss*L,,,L*******sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,.**....,,,.*******...,,,,,*********************************************L,,,L*sssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,,......,,,..,,,,,....,,,,,,,,,,,,*********,,,,....*****...,,,,,********,,,L*sssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss*L,,,,,......,,,..,,,,,....,,,,,,,,,,,,,,,,,,,,,,,....,,,,,.....,,,,,,,,,,,,,,,L*sssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**,,,,,,.HHHH,,,,b..,,,,HHHH,,,,,,,,,,,,,,,,,,,,,....,,,,,,,.....,,,,,,,,,,,,,,L*sssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss***********************************,,,,,,,,n,,,,,HHHH,,,,v,,,.HHHH,,,,,,n,,,,,,L*sssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss**********************************L,,,**************************************,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*L,,,L************************************L,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*L,,,L*****************ssssssssssssssssss*L,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*L,,,*************************************L,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssss*********************sssssssssssssssssssssssssss*L,,,,,,,,,,,,,,,,,,,**********************,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssss*********************sssssssssssssssssssssssssss*L,,,,,,,,,,,,,,,,,,,,,,,,........,,,,,,,,,,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssss**,,,,,,,,,,,,,,,,,**ssss**********sss************,,,v,,,,,,,,,n,,,,,,,,,........,,,,,,,,,,,,,L*sssssssssssssssssss";
	currentLevel += "sssssssssssss**,,,,,,,,,,,,,,,,,***********************************************,,,,,.........,,,,,,,,n,,,,,**sssssssssssssssssss";
	currentLevel += "sssssssssssss**,,,,,,,,,,,,,,,,,*******,,,,....*****,,,,....******************L,,,...........,,**************sssssssssssssssssss";
	currentLevel += "sssssssssssss****************,,,,,,,,,,,,,......,,,,,,,......,,,,,,,,**ssssss*L,,...........,,,L*************sssssssssssssssssss";
	currentLevel += "sssssssssssss***************L,,,,,,,,,,,,......,,,,,,,......,,,,,,,,,L*ssssss*L,...........,,,,L*************sssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*L,,,,,,,,,,,.HHHH.,,,,,,,,HHHH.,,,,,,,,,,L*ssssss**...b....b.,,,,,,L*******************sssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*L,,,**********************************,,,L*ssssss***************,,,*****....,,,,*******sssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*L,,,L********************************L,,,L*ssssss**************L,,,,,,,,.....,,,,,,,,**sssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*L,,,L*ssssssssssssssssssssssssssssss*L,,,L*sssssssssssssssssss*L,,,,,,,,,.....,,,,,,,**sssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*L,,,L*sssssssssssssssssssssssss******L,,,L*********************L,,,,,,n,,.HHHH,,,,v,,**sssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss*L,,,L*sssssssssssssssssssssssss*******,,,***********************,,,********************sssssssssssss";
	currentLevel += "ssssssssssssssssssss********L,,,L**************ssssssssssss**,,,,,,,,,,,...,,,,,,,,,,...,,,,,,,L*******************sssssssssssss";
	currentLevel += "sssssssssssssssssss**********,,,***************ssssssssssss**,,,,,,,,,....,,,,,,,,,,,,...,,,,,,L*sssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss***,,,,,,,,,,,....,,,,,,,,**ssssssssssss*L,,,,,,,,..b,,,,,,,,,,v,,,,b..,,,,,**sssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssss**,,,,,,,,,....,,,,,,,,,,,**s*********ss*L,,,************,,,******************sssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssss********,,,,,,,..b.,,,,,,,,,,,,,***************L,,,L**********L,,,L***********************************sssssssssssss";
	currentLevel += "ssssssssssss********,,,,,****************,,,,,***,,,,...*****,,,L*ssssssss*L,,,************************************sssssssssssss";
	currentLevel += "ssssssssssss***,,,,,,,,,******************,,,,,,,,,,.....,,,,,,,L*ssssssss*L,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssssssss";
	currentLevel += "ssssssssssss**s,,,,,,,,,**ssssssssssssss**,,,,,,,,,.....,,,,,,,,L*ssssssss*L,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssssssss";
	currentLevel += "ssssssssssss**sS,,,v,,,,**ssssssssssssss**,,,,n,,,,HHH.,,,v,,,,,**ssssssss**,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**sssssssssssss";
	currentLevel += "ssssssssssss**************ssssssssssssss**************************ssssssss*****************************************sssssssssssss";
	currentLevel += "sssssssssssss************ssssssssssssssss************************sssssssss*****************************************sssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

}

void Levels::CreateLevelTwelve()
{
	currentLevel = "";

	currentTileTxr = tileTextures[0];
	currentSong = songList[0];
	SetCurrentBackground(0);
	currentLevelWidth = 270;
	currentevelHeight = 34;
	cutsceneID = 0;
	spawnChar = L',';
	startCutscene = false;
	darkMode = false;
	miscChar = L',';

	
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss********************************sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssss******************************************************************sssssssss************************************sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss********************************************************************sssss******,,,,,.................,,,,,,,,*****sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss*r,,,,,,,,,,,,...,,,,,...,,..,,,*r,,,,,,,,,.........,,,,,..,,....,************,,,,....................,,,,,,,,,****sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss******s";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss*r,,,,,,,,,,,...,,,,...,,,...,,,*r,,,,,,,,.........,,,,,..,,....,,,*******,,,,,,........................,,,,,,,,,***sssssssssssssssssssssssssssssssssssssssss***********ssssssssssssssssssss**********ssssssssssssssssssss*********";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss*r,,,,,,,,,.....,,.....,,,HH.,,,*r,,,,,,,.........,,,,,..,,,HH.,,,,,,,,,,,,,,,.....................G.....,,,,,,,,,***ssssssss*********sssssssssssssssss*********************ssssssssssss******************ssssssssssss*******,,,,**";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss**,,,,,,,,,HH...,,HHH....,**,,,,,,,,,,,,HHHHHHHH.,,,,,..,,,,**,,,,,,,,,,,,,,,..............................,,,,,,,,**sssss**************sssssssssss***********,,,,,,,,,********ssssss********,,,,,,,,********ssssss********,,,,,,,*";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss**,,,,,,,,,**,.Z,,***,.Z..**,,,,.Z.,,,,,********,,,,,.Z,,,,,**,,,,,,,,,,,,,,....K...........................,,,,,,,L**ss******,,,,,,,****sssssss********,,,,,,.........,,,,******ss******,,,,,,,,,,,,,,,,******ss******,,,,,,,,,,,+";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss**,,,*********************************************************HHHHHHHH********************HHHHHHHHHHHHHHHHHHH,,,,,,L**s****,,,,,,,,,,,,*****ss******,,,,...................,,,********,,,,,,,,,,,,,,,,,,,,,,********,,,,,,,,,,,,,,+";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss**,,,********************************************************************************************************,,,,,,L*****,,,,,,,,,,,,,,,*********,,,..........................,,****,,,,,,,,,,,,,,,,,,,,,,,,,,****,,,,,,,,,,,,,,***";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssss**,,,,,,,..,,,,,,,,,,,,,,,***H.,,,,,,,**H.,,,,,,,**H.,,,,,,,**************sssssssssssssss*******************L,,,,,,L****,,,,,,,,,,,,,,,,,,,****,,..............................,,**,,,,,,,,,,,,,,,,,,,,,,,,,,,,**,,,,,,,,,,,,,*****";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssss***,,,,,,..,,,,,,,,,,,,,,.,,,**H.,,,.,,***H.,,,.,,***H.,,,.,,*****************sssssssssssssssssssssssssssss**L,,,,,,L***L,,,,,,,,,,,,,,,,,,,,,,,,.................................==,,,,,,,,,,,,,,,,,,,,,,,,,,,,==,,,,,,,,,,,*****ss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssss***,,,,,.C,,,,,,,,,,,,,,,,G,,,**H,,,,G,,,**H,,,,G,,,**H,,,,G,,,,,,,,,,,,,,******ssssssssssssssssssssssssssss*L,,,,,,L***L,,,,,,,,,,,,,,,,,,,,,,,...................C..............==,,,,,,,,,,,,,,,,,,,,,,,,,,,,==,,,,,,,,,*****ssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssss*****************HHHHHH,,,,.,,,**,,,,,.,,,**,,,,,.,,,**,,,,,.,,,,,,,.....,,,,****sssssssssssssssssssssssssss*L,,,,,,L***L,,,,,,,**********************************************************************************************ssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssss***************************,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....G....,,,,***sssssssssssssssssssssssss***,,,,,,L***L,,,,,,*********************************************************************************************ssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssss***********,,,,,,,,,,,,,,,,,,,,,,...,,,,,,,,....,,,,,....,,,,,....,,,,,..............,,,**sssssssssssssssssssssssss*r,,,,,,,L***L,,,,,,L**ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssss********,,,,,,...........................................................................,,**sssssssssssssssssssssssss*r,,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssss******,,,,,,,,..............................................................................,***ssssssssssssssssssssssss*r.,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssss****,,,,,,,,,................................................................................,,**ssssssssssssssssssssssss**H,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss***,,,,,,,,,,..................................................................................,**sssssssssssssssssssssssss**,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssss**,,,,,,,,,,,.............................................................................G.....**sssssssssssssssssssssssss**,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssss*************sssssss***,,,,,,,,,,...................................................................................H**ssssssssssssssssssssssss***,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssss***************ssssss**,,,,,,,,,,....................................................................................***ssssssssssssssssssssssss*r,,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssss**,,,,,,,,,,,**sssss***,,,,,,,,,.....................................................................................**sssssssssssssssssssssssss*r,,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssss**,,,,,,,,,,,**ss*****,,,,,,,,,.........................................................................G...........H**sssssssssssssssssssssssss*r.,,,,,,L***L,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssss**,,,,,,,,,,,********,,,,,,,,,,.........G..........................................................................H***sssssssssssssssssssssssss**H,,,,,,*****,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssss***,,,****,,,,,****,,,,,,,,,,,,....................................G.........................G....................HH***sssssssssssssssssssssssssss**,,,,,,,***,,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ss*****,,,*****,,,,,,,,,,,,,,,,,,,.................................................................................HHH****ssssssssssssssssssssssssssss*L,,,,,,....,,,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "s****,,,,,*****,,,,,,,,,,,,,,,,,,...........................Z.........................Z........................HHHH******sssssssssssssssssssssssssssss*L,,,,,.......,,,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "s**s,,,,,,***********************..........................**........................**.................HHHHHHH********sssssssssssssssssssssssssssssss*L,,,,..........,,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "s**sS,,,,,***********************HHHHHHHHHHHHHHHHHHHHHHHHHH**HHHHHHHHHHHHHHHHHHHHHHHH**HHHHHHHHHHHHHHHHH************ssssssssssssssssssssssssssssssssss*L,,.............,,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "s***********sssssssssssssssssss*********************************************************************************ssssssssssssssssssssssssssssssssssssss*L,...............,L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ss*********sssssssssssssssssssss*************************************************************************sssssssssssssssssssssssssssssssssssssssssssss*L.................L*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss**DDDDDDDDDDDDDDDDD**sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";




}


void Levels::CreateLevelThirteen()
{
	currentLevel = "";
	cutsceneID = 0;
	currentSong = songList[1];
	currentTileTxr = tileTextures[3];
	spawnChar = L'd';
	SetCurrentBackground(5);

	

	currentLevelWidth = 143;
	currentevelHeight = 22;

	currentLevel += "............................................................................................................................................###";
	currentLevel += "............................................................................................................................................##x";
	currentLevel += "............................................................................................................................................#x#";
	currentLevel += "%...........................................................................................................................................x##";
	currentLevel += "_...........................................................................................................................................###";
	currentLevel += "_...........................................................................................................................................##x";
	currentLevel += "_%..........................................................................................................................................#xx";
	currentLevel += "__..........................................................................................................................................###";
	currentLevel += "__..........................................................................................................................................#x#";
	currentLevel += "__..........................................................................................................................................x##";
	currentLevel += "sd..........................................................................................................................................##x";
	currentLevel += "sS.....................}{..}%%%%%%%%%%{...................}{..}%%%%%%%%%%{...................}{..}%%%%%%%%%%{...................}{..}%%%%%%____";
	currentLevel += "*%%%%%%{..[......}%%%%%%%%%%%%%%%%%%%%%%%%{..[......}%%%%%%%%%%%%%%%%%%%%%%%%{..[......}%%%%%%%%%%%%%%%%%%%%%%%%{..[......}%%%%%%%%%%%%%%%_dddd";
	currentLevel += "**%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%__ddsss";
	currentLevel += "**%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%__dddssss";
	currentLevel += "*d_%%%%%%%%%%%%%%%%%%%%%%%%%__________%%%%%%%%%%%%%%%%%%%%%%%%%__________%%%%%%%%%%%%%%%%%%%%%%%%%__________%%%%%%%%%%%%%%%%%%%%%%%%%_dddssssss";
	currentLevel += "*dd____%%%%%%%%%%%__________dddddddddd____%%%%%%%%%%%__________dddddddddd____%%%%%%%%%%%__________dddddddddd____%%%%%%%%%%%__________ddssssssss";
	currentLevel += "ssddddd___________dddddddddddsssssssssdddd___________dddddddddddsssssssssdddd___________dddddddddddsssssssssdddd___________dddddddddddsssssssss";
	currentLevel += "ssssssdddddddddddddssssssssssssssssssssssdddddddddddddssssssssssssssssssssssdddddddddddddssssssssssssssssssssssdddddddddddddsssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	currentLevel += "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

}

void Levels::CreateLevelFourteen()
{
}

void Levels::CreateLevelFifteen()
{
}

