package configure

import (
	"fmt"
	"github.com/paked/configure"
)

func hello() {
	conf := configure.New()
	name := conf.String("name", "hatlonely", "The name you want to greet")

	conf.Use(configure.NewEnvironment())
	conf.Use(configure.NewFlag())

	conf.Parse()
	fmt.Println("Hello ", *name)
}

func usage() string {
	return "this is a usage message"
}

func sublimetext() {
	conf := configure.New()
	colorscheme := conf.String("color_scheme", "", "")
	fontsize := conf.Int("font_size", 0, "")
	envpath := conf.String("PATH", "", "")
	conf.Use(configure.NewJSONFromFile("src/configure/configure.json"))
	conf.Use(configure.NewFlagWithUsage(usage))
	conf.Use(configure.NewEnvironment())

	conf.Parse()
	fmt.Println(*colorscheme, *fontsize, *envpath)
}

func Main() {
	hello()
	sublimetext()
}
