#pragma once
enum class Layer
{

	BACKGROUND,
	DEFAULT,
	ENEMY,
	PLAYER,
	PROJECTILE,
	ENEMYPROJECTILE,
	DAMAGETEXT,
	UI,
	END
};

// Layer용 비트마스크 타입 및 헬퍼
using LayerMask = unsigned int;

constexpr LayerMask LayerToMask(Layer l) noexcept
{
	return 1u << static_cast<unsigned int>(l);
}


constexpr LayerMask operator|(Layer a, Layer b) noexcept { return LayerToMask(a) | LayerToMask(b); }
constexpr LayerMask operator&(Layer a, Layer b) noexcept { return LayerToMask(a) & LayerToMask(b); }
constexpr LayerMask operator^(Layer a, Layer b) noexcept { return LayerToMask(a) ^ LayerToMask(b); }

constexpr LayerMask operator|(LayerMask m, Layer l) noexcept { return m | LayerToMask(l); }
constexpr LayerMask operator&(LayerMask m, Layer l) noexcept { return m & LayerToMask(l); }
constexpr LayerMask operator^(LayerMask m, Layer l) noexcept { return m ^ LayerToMask(l); }

inline LayerMask& operator|=(LayerMask& m, Layer l) noexcept { m |= LayerToMask(l); return m; }
inline LayerMask& operator&=(LayerMask& m, Layer l) noexcept { m &= LayerToMask(l); return m; }
inline LayerMask& operator^=(LayerMask& m, Layer l) noexcept { m ^= LayerToMask(l); return m; }

constexpr bool HasFlag(LayerMask m, Layer l) noexcept { return (m & LayerToMask(l)) != 0u; }


enum class PenType
{
	RED, GREEN, CARDTEXT, END
};
enum class BrushType
{
	HOLLOW, RED, GREEN,  END
};

enum class FontType
{
	UI, TITLE,CARDDESC, CARDTITLE, END
};

enum class PlayMode
{
	Once, Loop, Counted
};