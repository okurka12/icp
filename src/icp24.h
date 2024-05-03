/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file Constants for the simulation
*/

#ifndef ICP24_H
#define ICP24_H

#define ICP_TITLE "ICP24"
#define ICP_WIDTH 1280
#define ICP_HEIGHT 720

/* ticks per second */
#define ICP_TPS 70

/* obstacle size in px */
#define ICP_OBSIZE 25

/* radius of a robot in px */
#define ICP_ROBSIZE 50

/* radius of a robot head in px */
#define ICP_ROBHEAD_SIZE 10

/* how thick is a robot outline in px */
#define ICP_ROBOT_OUTLINE 5

/* speed of a robot in pixels/s */
#define ICP_ROBSPEED 200

/* speed of a robot rotation if collision is detected, degrees per second */
#define ICP_ROBROT 90

/* initial angle in degrees for a newly spawned robot */
#define ICP_INIT_ANGLE 325

/* initial x pos of a newly spawned robot (px) */
#define ICP_INIT_X 100

/* initial y pos of a newly spawned robot (px) */
#define ICP_INIT_Y 100

/* pi */
#define ICP_PI 3.14159265359

/* margin of collision detection, px */
#define ICP_MARGIN 2

/* macro to convert degrees to radians (double) */
#define ICPdeg2rad(rrrad) (((double)(rrrad) / 180.0) * ICP_PI)

#endif // ifndef ICP24_H
