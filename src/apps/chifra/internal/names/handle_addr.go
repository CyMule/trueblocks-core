package namesPkg

import (
	"context"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/names"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/output"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/types"
)

func (opts *NamesOptions) HandleAddr() error {
	namesArray, err := names.LoadNamesArray(opts.Globals.Chain, opts.getType(), names.SortByAddress)
	if err != nil {
		return err
	}
	if opts.Globals.TestMode {
		namesArray = namesArray[:200]
		if opts.Custom {
			namesArray = []names.Name{}
			namesArray = append(namesArray, names.Name{Address: "0x1"})
			namesArray = append(namesArray, names.Name{Address: "0x2"})
			namesArray = append(namesArray, names.Name{Address: "0x3"})
			namesArray = append(namesArray, names.Name{Address: "0x4"})
		}
	}

	ctx := context.Background()

	// Note: Make sure to add an entry to enabledForCmd in src/apps/chifra/pkg/output/helpers.go
	fetchData := func(modelChan chan types.Modeler[types.RawPart], errorChan chan error) {
		for _, name := range namesArray {
			s := types.SimplePart{
				Address: types.HexToAddress(name.Address),
			}
			modelChan <- &s
		}
	}

	return output.StreamMany(ctx, fetchData, output.OutputOptions{
		Writer:     opts.Globals.Writer,
		Chain:      opts.Globals.Chain,
		TestMode:   opts.Globals.TestMode,
		NoHeader:   true,
		ShowRaw:    opts.Globals.ShowRaw,
		Verbose:    opts.Globals.Verbose,
		LogLevel:   opts.Globals.LogLevel,
		Format:     opts.Globals.Format,
		OutputFn:   opts.Globals.OutputFn,
		Append:     opts.Globals.Append,
		JsonIndent: "  ",
		Extra: map[string]interface{}{
			"address": true,
		},
	})
}
