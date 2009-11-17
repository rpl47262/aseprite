/* ASE - Allegro Sprite Editor
 * Copyright (C) 2001-2009  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

#include "jinete/jbase.h"

#include "commands/command.h"
#include "raster/layer.h"
#include "raster/mask.h"
#include "raster/sprite.h"
#include "util/clipboard.h"
#include "sprite_wrappers.h"
#include "util/misc.h"

class CutCommand : public Command
{
public:
  CutCommand();
  Command* clone() const { return new CutCommand(*this); }

protected:
  bool enabled(Context* context);
  void execute(Context* context);
};

CutCommand::CutCommand()
  : Command("cut",
	    "Cut",
	    CmdUIOnlyFlag)
{
}

bool CutCommand::enabled(Context* context)
{
  const CurrentSpriteReader sprite(context);
  if ((sprite) &&
      (sprite->layer) &&
      (sprite->layer->is_readable()) &&
      (sprite->layer->is_writable()) &&
      (sprite->mask) &&
      (sprite->mask->bitmap))
    return GetImage(sprite) ? true: false;
  else
    return false;
}

void CutCommand::execute(Context* context)
{
  CurrentSpriteWriter sprite(context);
  clipboard::cut(sprite);
}

//////////////////////////////////////////////////////////////////////
// CommandFactory

Command* CommandFactory::create_cut_command()
{
  return new CutCommand;
}
