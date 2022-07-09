// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package whenPkg

import (
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/identifiers"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/tslib"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/types"
)

// HandleWhenTimestampsShow handles chifra when --timestamps
func (opts *WhenOptions) HandleWhenTimestampsShow() error {
	cnt, err := tslib.NTimestamps(opts.Globals.Chain)
	if err != nil {
		return err
	}

	err = opts.Globals.RenderHeader(tslib.Timestamp{}, &opts.Globals.Writer, opts.Globals.Format, opts.Globals.ApiMode, opts.Globals.NoHeader, true)
	defer opts.Globals.RenderFooter()
	if err != nil {
		return err
	}

	prev := types.SimpleTimestamp{}
	blockNums, err := identifiers.GetBlockNumbers(opts.Globals.Chain, opts.BlockIds)
	if err != nil {
		return err
	}
	// We use the first block as the starting point. The user may have added additional blocks, but we ignore them
	if len(blockNums) > 0 {
		prev.BlockNumber = blockNums[0]
	}

	for bn := prev.BlockNumber; bn < cnt; bn++ {
		ts, err := tslib.FromBn(opts.Globals.Chain, bn)
		if err != nil {
			return err
		}
		obj := types.SimpleTimestamp{
			BlockNumber: uint64(bn*100000000) + uint64(ts.Bn),
			TimeStamp:   uint64(ts.Ts),
			Diff:        uint64(ts.Ts - uint32(prev.TimeStamp)),
		}
		if bn == prev.BlockNumber {
			// Report zero diff at first block
			obj.Diff = 0
		}
		err = opts.Globals.RenderObject(obj, bn == 0)
		if err != nil {
			return err
		}
		prev = obj
	}
	return nil
}
