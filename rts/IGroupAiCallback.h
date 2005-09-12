#ifndef IGROUPAICALLBACK_H
#define IGROUPAICALLBACK_H
// IGroupAICallback.h: interface for the IGroupAICallback class.
// Dont modify this file
//////////////////////////////////////////////////////////////////////

#pragma warning(disable:4786)

#include <vector>
#include <deque>
#include "float3.h"
#include "command.h"

struct UnitDef;
struct FeatureDef;

class IGroupAICallback  
{
public:
	virtual void SendTextMsg(const char* text,int priority)=0;		//sends a text message to the local user, lower priority ones might be filtered to avoid flooding

	virtual int GetCurrentFrame()=0;															//get the current game time, there is 30 frames per second at normal speed
	virtual int GetMyTeam()=0;
	virtual int GetMyAllyTeam()=0;
	virtual int GetPlayerTeam(int player)=0;

	// returns the size of the created area, this is initialized to all 0 if not previously created
	//set something to !0 to tell other ais that the area is already initialized when they try to create it
	//the exact internal format of the memory areas is up to the ais to keep consistent
	virtual void* CreateSharedMemArea(char* name, int size)=0;
	//release your reference to a memory area.
	virtual void ReleasedSharedMemArea(char* name)=0;

	virtual int GiveOrder(int unitid,Command* c)=0;					//gives a order to a unit under the groups control, see also command.h
	virtual void UpdateIcons()=0;														//force gui to update the icons 
	virtual const Command* GetOrderPreview()=0;									//this make the game to try to create an order from the current (unfinished) mouse state, dont count on the command being pointed to being left after you call this again or leave the function
	virtual bool IsSelected()=0;													//returns true if this group is currently selected

	virtual int GetUnitLastUserOrder(int unitid)=0;	//last frame the user gave a direct order to a unit, ai should probably leave it be for some time to avoid irritating user
	virtual const vector<CommandDescription>* GetUnitCommands(int unitid)=0;	//the commands that this unit can understand, other commands will be ignored
	virtual const deque<Command>* GetCurrentUnitCommands(int unitid)=0;	//the commands that this unit has currently qued

	//all the following returns 0 if you dont have los to the unit in question (including null pointers ... )
	virtual int GetUnitAihint(int unitid)=0;				//integer telling something about the units main function, not currently working hopefully will soon
	virtual int GetUnitTeam(int unitid)=0;
	virtual int GetUnitAllyTeam(int unitid)=0;
	virtual float GetUnitHealth(int unitid)=0;			//the units current health
	virtual float GetUnitMaxHealth(int unitid)=0;		//the units max health
	virtual float GetUnitSpeed(int unitid)=0;				//the units max speed
	virtual float GetUnitPower(int unitid)=0;				//sort of the measure of the units overall power
	virtual float GetUnitExperience(int unitid)=0;	//how experienced the unit is (0.0-1.0)
	virtual float GetUnitMaxRange(int unitid)=0;		//the furthest any weapon of the unit can fire
	virtual const UnitDef* GetUnitDef(int unitid)=0;	//this returns the units unitdef struct from which you can read all the statistics of the unit, dont try to change any values in it, dont use this if you dont have to risk of changes in it

	virtual const UnitDef* GetUnitDef(const char* unitName)=0;		//this returns the unitdef for a given unit type

	//this will return a value even if you only have radar to it, but it might be wrong
	virtual float3 GetUnitPos(int unitid)=0;				//note that x and z are the horizontal axises while y represent height

	//the following functions allows the dll to use the built in pathfinder
	//call InitPath and you get a pathid back
	//use this to call GetNextWaypoint to get subsequent waypoints, the waypoints are centered on 8*8 squares
	//note that the pathfinder calculates the waypoints as needed so dont retrieve them until they are needed
	//the waypoints x and z coordinate is returned in x and z while y is used for error codes
	//>=0 =worked ok,-2=still thinking call again,-1= end of path reached or invalid path
	virtual int InitPath(float3 start,float3 end,int pathType)=0;
	virtual float3 GetNextWaypoint(int pathid)=0;
	virtual void FreePath(int pathid)=0;

	//This function returns the approximate path cost between two points(note that it needs to calculate the complete path so its somewhat expansive)
	virtual float GetPathLength(float3 start,float3 end,int pathType)=0;

	//the following function return the units into arrays that must be allocated by the dll
	//10000 is currently the max amount of units so that should be a safe size for the array
	//the return value indicates how many units was returned, the rest of the array is unchanged
	virtual int GetEnemyUnits(int *units)=0;					//returns all known enemy units
	virtual int GetEnemyUnits(int *units,const float3& pos,float radius)=0; //returns all known enemy units within radius from pos
	virtual int GetFriendlyUnits(int *units)=0;					//returns all friendly units
	virtual int GetFriendlyUnits(int *units,const float3& pos,float radius)=0; //returns all friendly units within radius from pos

	//the following functions are used to get information about the map
	//dont modify or delete any of the pointers returned
	//the maps are stored from top left and each data position is 8*8 in size
	//to get info about a position x,y look at location
	//(int(y/8))*GetMapWidth()+(int(x/8))
	//some of the maps are stored in a lower resolution than this though
	virtual int GetMapWidth()=0;
	virtual int GetMapHeight()=0;
	virtual const float* GetHeightMap()=0;						//this is the height for the center of the squares, this differs slightly from the drawn map since it uses the height at the corners
	virtual const unsigned short* GetLosMap()=0;			//a square with value zero means you dont have los to the square, this is half the resolution of the standard map
	virtual const unsigned short* GetRadarMap()=0;		//a square with value zero means you dont have radar to the square, this is 1/8 the resolution of the standard map
	virtual const unsigned short* GetJammerMap()=0;		//a square with value zero means you dont have radar jamming on the square, this is 1/8 the resolution of the standard map
	virtual const unsigned char* GetMetalMap()=0;			//this map shows the metal density on the map, this is half the resolution of the standard map
	virtual const char* GetMapName()=0;
	virtual const char* GetModName()=0;

	virtual float GetElevation(float x,float z)=0;		//Gets the elevation of the map at position x,z

	//the following functions allow the ai to draw figures in the world
	//each figure is part of a group
	//when creating figures use 0 as group to get a new one, the return value is the new group
	//the lifetime is how many frames a figure should live before being autoremoved, 0 means no removal
	//arrow!=0 means that the figure will get an arrow at the end
	virtual int CreateSplineFigure(float3 pos1,float3 pos2,float3 pos3,float3 pos4,float width,int arrow,int lifetime,int group)=0;	//This function creates a cubic beizer spline figure
	virtual int CreateLineFigure(float3 pos1,float3 pos2,float width,int arrow,int lifetime,int group)=0;
	virtual void SetFigureColor(int group,float red,float green,float blue,float alpha)=0;
	virtual void DeleteFigureGroup(int group)=0;

	//this function allows you to draw units in the map, of course they dont really exist,they just show up on the local players screen
	//they will be drawn in the standard pose before any scripts are run
	//the rotation is in radians,team affects the color of the unit
	virtual void DrawUnit(const char* name,float3 pos,float rotation,int lifetime,int team,bool transparent,bool drawBorder)=0;

	virtual bool CanBuildAt(const UnitDef* unitDef,float3 pos)=0; //returns true if a given type of unit can be build at a pos (not blocked by other units etc)
	virtual float3 ClosestBuildSite(const UnitDef* unitdef,float3 pos,float searchRadius,int minDist)=0;	//returns the closest position from a position that the building can be built, minDist is the distance in squares that the building must keep to other buildings (to make it easier to create paths through a base), returns x=-1 if a pos is not found

	virtual float GetMetal()=0;				//stored metal for team
	virtual float GetMetalIncome()=0;				
	virtual float GetMetalUsage()=0;				
	virtual float GetMetalStorage()=0;				//metal storage for team

	virtual float GetEnergy()=0;				//stored energy for team
	virtual float GetEnergyIncome()=0;			
	virtual float GetEnergyUsage()=0;				
	virtual float GetEnergyStorage()=0;				//energy storage for team

	virtual int GetFeatures (int *features, int max)=0;
	virtual int GetFeatures (int *features, int max, const float3& pos, float radius)=0;
	virtual FeatureDef* GetFeatureDef (int feature)=0;
	virtual float GetFeatureHealth (int feature)=0;
	virtual float GetFeatureReclaimLeft (int feature)=0;
};

#endif /* IGROUPAICALLBACK_H */
