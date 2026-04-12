SET @ENTRY := 190011;

-- Remove existing spawns for this NPC entry
DELETE FROM `creature` WHERE `id1` = @ENTRY;

INSERT INTO `creature`
(
    `guid`,
    `id1`,
    `id2`,
    `id3`,
    `map`,
    `zoneId`,
    `areaId`,
    `spawnMask`,
    `phaseMask`,
    `equipment_id`,
    `position_x`,
    `position_y`,
    `position_z`,
    `orientation`,
    `spawntimesecs`,
    `wander_distance`,
    `currentwaypoint`,
    `curhealth`,
    `curmana`,
    `MovementType`,
    `npcflag`,
    `unit_flags`,
    `dynamicflags`,
    `ScriptName`,
    `VerifiedBuild`,
    `CreateObject`,
    `Comment`
)
VALUES
(900001, @ENTRY, 0, 0,   0, 0, 0, 1, 1, 0,  2225.25,   311.842,   36.7217, 0.8508,    300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900002, @ENTRY, 0, 0, 530, 0, 0, 1, 1, 0,  9478.25, -6797.82,   16.4935, 6.09441,   300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900003, @ENTRY, 0, 0,   1, 0, 0, 1, 1, 0,   368.3,  -4708.13,   16.0304, 3.96385,   300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900004, @ENTRY, 0, 0,   1, 0, 0, 1, 1, 0, -2267.43,  -326.764,  -9.42422, 2.25942,  300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900005, @ENTRY, 0, 0,   0, 0, 0, 1, 1, 0, -5569.6,   -426.344, 397.326,   3.8433,   300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900006, @ENTRY, 0, 0,   0, 0, 0, 1, 1, 0, -9465.22,    95.8764, 58.3419,  0.124427, 300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900007, @ENTRY, 0, 0, 530, 0, 0, 1, 1, 0, -4238.69, -12531.5,   45.7146, 0.0424266, 300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL),
(900008, @ENTRY, 0, 0,   1, 0, 0, 1, 1, 0,  9841.46,   950.278, 1307.45,   5.57317,  300, 0, 0, 12600, 0, 0, 0, 0, 0, '', NULL, 0, NULL);