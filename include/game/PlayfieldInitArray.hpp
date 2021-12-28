#ifndef PLAYFIELDINITARRAY_HPP_
#define PLAYFIELDINITARRAY_HPP_

#include "Playfield.hpp"

static constexpr
std::array<std::array<Playfield::TileType, Playfield::kFieldWidth>,
                            Playfield::kFieldHeight> kPlayfieldInitArray
{{
    { Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::Water, Playfield::TileType::Coast,
      Playfield::TileType::Peat, Playfield::TileType::Forest,
      Playfield::TileType::Forest, Playfield::TileType::Forest,
      Playfield::TileType::Hill, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::Water, Playfield::TileType::Coast,
      Playfield::TileType::Peat, Playfield::TileType::Forest,
      Playfield::TileType::Forest, Playfield::TileType::Forest,
      Playfield::TileType::Forest, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None },
    { Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None, Playfield::TileType::None,
      Playfield::TileType::None },
}};

#endif // PLAYFIELDINITARRAY_HPP_
