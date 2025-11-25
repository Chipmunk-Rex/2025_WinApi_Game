#pragma once
enum class Layer
{
	UI,
	BACKGROUND,
	DEFAULT,
	PLAYER,
	ENEMY,
	PROJECTILE,
	ENEMYPROJECTILE,
	END
};
enum class PenType
{
	RED, GREEN, END
};
enum class BrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode
{
	Once, Loop, Counted
};