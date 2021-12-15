#ifndef PLAYFIELDINITARRAY_HPP_
#define PLAYFIELDINITARRAY_HPP_

#include "Tile.hpp"
#include "Playfield.hpp"

static constexpr std::array<std::array<Tile::TileType, Playfield::kFieldWidth>,
                            Playfield::kFieldHeight> kPlayfieldInitArray
{{
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Peat,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Hill, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Peat,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Peat,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Hill, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Peat,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill },
    { Tile::TileType::Water, Tile::TileType::Coast, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
      Tile::TileType::Forest, Tile::TileType::Hill, Tile::TileType::Hill }
}};

#endif // PLAYFIELDINITARRAY_HPP_
