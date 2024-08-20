#include "levels.h"

void Levels::CreateLevelOne()
{


	currentLevel = "";

	currentLevelWidth = 102;
	currentevelHeight = 32;

	currentLevel += "__##--##______________________________________________________________________________________________";
	currentLevel += "**##--##***************_********************************___************************_************_____*";
	currentLevel += "**##-,##,,,=,,,,,.....***..B.,,,,,=,,,,,,,,,,,,,,,,,,,,*****,,,,,,,,,,,,,***,,..,,***,,,,,,,,,********";
	currentLevel += "**##,,#,,,,=,,,,.......*....B.,,,,=,,,,,.,,,,,,,,,,,,,,,***,,,,...,,,,,,,,*,,,..,,,*,,,,,,,,,,,,,*****";
	currentLevel += "**#,,,,,,,,=,,,........*.....B.,,,=,,,,,..,,,,,,,,,,,,,,,*,,,,,,.,,,,,,,,,,,,....,,*,,,,,,,,,,,,,,,***";
	currentLevel += "**,,,,,,,,,=,,................B.,,=,,3,....,,,,,,,,,,,,,,*,,,,,,,,,,,,,,,,,.......,,,,,,,,,,,,,,,,,***";
	currentLevel += "+,,,,,,,,,,=,.................B..,=,,,,,...,,,,,,,,,,,,,..,,,,,,,,,*,,,,,..........,,,,,,,,,,,,,,,,,**";
	currentLevel += "+,,,,,,,,,,=..................B...=,,C,,,,,,,,,,,,,,,,......,,,,,,,*,,,,,,..........,,,,,,,,,,,,,,,,**";
	currentLevel += "__##,,#*****...[.{.}...K..{.].B[..******,,,,,,,,,,,,,,.]..{...,,,,***,,,,..[..Z....}..,,,,,,,,,,,,,,**";
	currentLevel += "**##,-##*******________________*********,,,,,,,,**______________******_____________________***,,,,,,**";
	currentLevel += "**##--##**********__________************,,,,,,,,*****________************_______________******,,,,,,**";
	currentLevel += "**##--##********************************,,,,,,,,********___*****************____*****__******,,,,,,,**";
	currentLevel += "**##--##********************************,,..,,,,********************************************,,,,,,****";
	currentLevel += "**##--##********************************,,.,,,,,********************************************,,,,,,,***";
	currentLevel += "**##--##********************************,,,,,,,,********************************************,,,,,,,,**";
	currentLevel += "**##--##********************************,,,,,,,,********************************************,,,,,,,,**";
	currentLevel += "**##--##********************************,,,,,,,,**********************************************,,,,,,**";
	currentLevel += "**##--##********************************,,,,,,,,,********************************************,,,,,,,**";
	currentLevel += "**##--##********************************,,,,,,,,,,,,*******************...............*****,,,,,,,,,**";
	currentLevel += "**##--##*******************************,,,,,,,,,,,,,,,,**************.....................,,,,,,,,,,**";
	currentLevel += "**##--##*****************************,,,,,,,,,,..,,,,,,,,,*********........................,,,,,,*****";
	currentLevel += "**##--##***************************,,,,,,,,,,,....,,,,,,,,,,,****...2......................,,,,,,,,***";
	currentLevel += "**##,,##*************************,,,,,,,,,,,,...,,,,,,,,,,,,,,,,............................,,,,,,,,**";
	currentLevel += "**##,,##************************,,,,,,,,,,,,...,,,,,,,,,,,,,,,,,..}...[....].......Z..[..{...,,,,,,,**";
	currentLevel += "*##,,,,##**********************,,,,,,,,,,,,.{.].,,,,,,,,**_______________________________________*****";
	currentLevel += "*#,,,,,,,,,,,*****************,,,,,,,,,,**_____**,,,,,,*****_______****_________________________******";
	currentLevel += "**,,,,,,,,,,,,,,,,,,,......,,,,,,,,,,,,,***___***,,,,,,*******___************_________________********";
	currentLevel += "**,,,,,,,,,,,,,,,,,,......,,,,,,,,,,,,,,*********,,,,,,*********************************____**********";
	currentLevel += "**,..,,,,,,,,,,,,,,..}..[.,,,,,,,,,,,,,,,*******,,,,,,,***********************************************";
	currentLevel += "**,,S1,,,,,,,***____________________**,,,,,,,,,,,,,,,,,***********************************************";
	currentLevel += "**,.{.],************______________*****,,,,,,,,,,,,,,,,***********************************************";
	currentLevel += "***____*******************_____***********************************************************************";

	bossChar = L'K';
}

void Levels::CreateLevelTwo()
{
	currentLevel = "";

	currentLevelWidth = 128;
	currentevelHeight = 22;
	
	currentLevel += ".............................................................................................................................###";
	currentLevel += "............................................................................................................................####";
	currentLevel += "...........................................................................................................................#####";
	currentLevel += "%.........................................................................................................................######";
	currentLevel += "_........................................................................................................................#######";
	currentLevel += "_.......................................................................................................................########";
	currentLevel += "_%.....................................................................................................................#########";
	currentLevel += "__.....................................................................................................................#########";
	currentLevel += "__.....................................................................................................................#########";
	currentLevel += "__.....................................................................................................................--------#";
	currentLevel += "__..........................#--#................................................................................Z......--------+";
	currentLevel += "__%.......%%%%%%%%%%%%%%%%%%#--#%%%%%%......................................................................%%%%%%%%%%%##------+";
	currentLevel += "___%........________________#--#______%%%%%....................%%%%%%%%%%%%.........................%%%%%%%%____________########";
	currentLevel += "____%..........s____________#--#___________%%%%....Z.....%%%%%%____________%%%%%......Z.....%%%%%%%%____________________________";
	currentLevel += "_____%........Ss____________#--#_______________%%%%%%%%%%_______________________%%%%%%%%%%%%____________________________________";
	currentLevel += "______%%%%%%%%%%____________#--#________________________________________________________________________________________________";
	currentLevel += "____________________________#--#________________________________________________________________________________________________";
	currentLevel += "____________________________#--#________________________________________________________________________________________________";
	currentLevel += "____________________________#--#________________________________________________________________________________________________";
	currentLevel += "____________________________#--#________________________________________________________________________________________________";
	currentLevel += "____________________________#--#________________________________________________________________________________________________";
	currentLevel += "____________________________#DD#________________________________________________________________________________________________";

}

void Levels::CreateLevelThree()
{
	currentLevel = "";

	currentLevelWidth = 128;
	currentevelHeight = 22;

	currentLevel += "____##......................................................###..........................###..................................##";
	currentLevel += "_____##....................................................#_#_#........................#_#_#..................................+";
	currentLevel += "########..................................................#_#_#_#......................#_#_#_#.................................+";
	currentLevel += "#########................................................#########B...................#########..............................#_#";
	currentLevel += "##########.......................................................=.B..................=.......................................#_";
	currentLevel += "###########......................................................=.B..................=.......................................##";
	currentLevel += "###########..................................................C...=.B..................=...Z...................................#_";
	currentLevel += "###########..............................................#########B...................#########..............................#_#";
	currentLevel += "###########..............................................#_#_#_#_#....................#_#_#_#_#...............................#_";
	currentLevel += "s----------..............................................##_#_#_##....................##_#_#_##...............................##";
	currentLevel += "sS---------................Z............................##_#_#_#_#..........K.........#_#_#_#_#...............................#_";
	currentLevel += "###########%%%%%%%%%%%%%%%%%%%%%%%%%%%...................##_#_#_#_#######%%%%%%################..............................#_#";
	currentLevel += "______________________________________%%%%%..............#___________________________________##..............................##_";
	currentLevel += "___________________________________________%%%%.....Z....#___________________________________##..............................#_#";
	currentLevel += "_______________________________________________%%%%%%%%%%#___________________________________##..............................##_";
	currentLevel += "_____________________________________________________________________________________________##.............................##_#";
	currentLevel += "_____________________________________________________________________________________________##.............................#_#_";
	currentLevel += "_____________________________________________________________________________________________##.............................##_#";
	currentLevel += "_____________________________________________________________________________________________###............................#_#_";
	currentLevel += "______________________________________________________________________________________________##..........................##_#_#";
	currentLevel += "______________________________________________________________________________________________###............Z...........##_#_#_";
	currentLevel += "______________________________________________________________________________________________####%%%%%%%%%%%%%%%%%%%%%%########";
	
	bossChar = L'K';
}

void Levels::CreateLevelFour()
{
	currentLevel = "";

	currentLevelWidth = 128;
	currentevelHeight = 64;
	currentLevel += "............#################################################################............###.................#######...........#";
	currentLevel += "............##################################################################..........#####...............########...........#";
	currentLevel += "............###----....----....----....----....----....----....--------####----.........-----..............------###...........#";
	currentLevel += "............###----....----....----....----....----....----....---------##------B-....--------..........---------###...........#";
	currentLevel += "............###----....----....----....----....----....----....---------##------B--..-----------......-----------###...........#";
	currentLevel += "............###----....----....----....----....----....----....---------##------B----------------...-------------###...........#";
	currentLevel += "............-------....----....----....----....----....----....---------##------B--------------------------------###...........#";
	currentLevel += "............-------....----....----....----....----....----....----------=------B---------------------------------=--.-.-.-.-.-+";
	currentLevel += "..........#.-C------..------..------..------..------..------..-----------=------B--------------N------------------=------------+";
	currentLevel += "..........######################################################################################################################";
	currentLevel += "...........##########################################################################################################.........##";
	currentLevel += "............###---------------------------------------------------------------------------------------------########...........#";
	currentLevel += "...####.....###---------------------------------------------------------------------.....---------------------######...........#";
	currentLevel += "...-##-.....-----------------------------..----------------------------------------.......---------------------#####...........#";
	currentLevel += "....----....----------------------------....------------------.-------------------........----------------------####...........#";
	currentLevel += ".....----.########--------------------..........--------------.-----------------...........---------------------#####...........";
	currentLevel += "......-----################---------.............-------------..---------------............----------------------####...........";
	currentLevel += "........----###############--------...--...K...-...----------....--------------..............--------------------####...........";
	currentLevel += ".........---###############------####################--------....----------------..........----------------------####...........";
	currentLevel += "..........--###############------####################--------####----------------------K-------------------------###............";
	currentLevel += "DDDDDDDDDDDD###############------####################---------##---------###########################-------------###............";
	currentLevel += "............###############------####################----------------------############################----------###............";
	currentLevel += "............###############------####################--------------------------------....------------#####-------###............";
	currentLevel += "...........################-------##################------------------------------...........--------------------####...........";
	currentLevel += "...........################-------##################------------------------------.............------------------####...........";
	currentLevel += "...........################--------################--------------------------------...-..K...-.------------Z-----####...........";
	currentLevel += "...........###############-----------------------------------------.----#############################################...........";
	currentLevel += "............############---------------------------------.---------.----############################################............";
	currentLevel += "............#######--------------------------------------..-------...---############################################............";
	currentLevel += "............###-----------------------------------------...-------###---############################################............";
	currentLevel += "............###-------------------###################---###-------##----############################################............";
	currentLevel += "...........####---------------C---###################----##-------------#############################################..........."; 
	currentLevel += "...........####------------##########################-------------------#############################################..........."; 
	currentLevel += "...........####------------##########################-------------------#############################################...........";
	currentLevel += "...........####----------############################-------------------###################-------------------#######...........";
	currentLevel += "............###-------###############################---------.---------#############--------------.-------------###............";
	currentLevel += "............###-------####------------------------------------.-----------------------------------...-------------##............";
	currentLevel += "............###----------------------------------------------..------------------------------------.----------------............";
	currentLevel += "............###--------Z------------------K------------------...-------------------------------K--------------------............";
	currentLevel += "...........############################################------###------#########################################-----............";
	currentLevel += "...........############################################------###------##############################################............";
	currentLevel += "...........###########################################--------#--------#############################################............";
	currentLevel += "...........###########################################-------...-------#############################################............";
	currentLevel += "............#########################################--------...--------############################################......####..";
	currentLevel += "............#########################################--------...--------##########################################--.......##...";
	currentLevel += "............#########################################-----.........-----#########################################--........--...";
	currentLevel += "............#########################################-----.........-----#########################################--.....-----...";
	currentLevel += "...........#########################################---------...---------###########################################-------.....";
	currentLevel += "...........########################################----------...----------#####################-----------##########-----.......";
	currentLevel += "...........####################################--------------...--------------#########------------.---------#######--..........";
	currentLevel += "...........#######-----------------------------------------.-...-.--------------------------------...---------------............";
	currentLevel += "............###---.---------------.-----------------------...-.-...---------------.---------------...---------------....####....";
	currentLevel += "............###--...-------------...-------------------.--...-.-...--.-----------...---------------.----------------.....##.....";
	currentLevel += "............###--...-------------...------------------..--...---...--..----------...--------------------K-----------.....--.....";
	currentLevel += "............###--...-------------...------------------..--...---...--..----------...---------#######################....---.....";
	currentLevel += "............###--...-------------...-------------------.--...---...--.-----------...---------#######################..----......";
	currentLevel += "...........####---.---------------.-----------------------...---...---------------.----------#######################-----.......";
	currentLevel += "...........####------------------------Z-------------------.-----.-------------Z-------------#######################----........";
	currentLevel += "...........##########------#########################----------K---------###############------#######################---.........";
	currentLevel += "...........#########------#############################################################------#######################--..........";
	currentLevel += "............#######s-----##############################################################------#######################-...........";
	currentLevel += "............#######sS---###############################################################------#######################............";
	currentLevel += "............###########################################################################------#######################............";
	currentLevel += "............###########################################################################DDDDDD#######################DDDDDDDDDDDD";

	bossChar = L'N';
}

void Levels::CreateLevelFive()
{

	currentLevel = "";

	currentLevelWidth = 62;
	currentevelHeight = 12;
	currentLevel += "##############################################################";
	currentLevel += "##############################################################";
	currentLevel += "####--....----....----....----....----....----....--##########";
	currentLevel += "###---....----....----....----....----....----....---#########";
	currentLevel += "###---....----....----....----....----....----....---#########";
	currentLevel += "###---....----....----....----....----....----....---#########";
	currentLevel += "s-----....----....----....----....----....----....----########";
	currentLevel += "sS----....----....----....----....----....----....-----------E";
	currentLevel += "s------..------..------..------..------..------..------------E";
	currentLevel += "##############################################################";
	currentLevel += "##############################################################";
	currentLevel += "##############################################################";
}
