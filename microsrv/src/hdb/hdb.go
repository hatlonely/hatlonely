package hdb

import (
	"github.com/cihub/seelog"
	"github.com/spf13/viper"
	"gopkg.in/gin-gonic/gin.v1"
	"net/http"
	"store"
)

var route *gin.Engine
var level *store.HLevel
var hlog seelog.LoggerInterface
var config *viper.Viper

func init() {
	level = &store.HLevel{}
	config = viper.New()

	config.SetDefault("dbpath", "data/leveldb")
	config.SetDefault("address", ":6001")
}

func Init() error {
	{
		var err error
		if hlog, err = seelog.LoggerFromConfigAsFile("conf/hdb_logger.xml"); err != nil {
			return seelog.Errorf("init hlog failed. err: [%v]", err)
		}
	}
	{
		config.AddConfigPath("conf")
		config.SetConfigName("hdb")
		config.SetConfigType("json")
		if err := config.ReadInConfig(); err != nil {
			return seelog.Errorf("init config failed. err: [%v]", err)
		}
	}
	{
		if err := level.Init(config.GetString("dbpath")); err != nil {
			return seelog.Errorf("init hlevel failed. err: [%v]", err)
		}
	}

	route = gin.Default()

	route.GET("/get", func(context *gin.Context) {
		key := context.Query("key")
		if key == "" {
			context.String(http.StatusBadRequest, "miss key")
			return
		}
		if val, err := level.GetString(key); err == nil {
			context.String(http.StatusOK, val)
		} else {
			context.String(http.StatusInternalServerError, "%v", err)
		}
	})

	route.GET("/set", func(context *gin.Context) {
		key := context.Query("key")
		val := context.Query("val")
		if key == "" {
			context.String(http.StatusBadRequest, "miss key")
			return
		}
		if err := level.PutString(key, val); err == nil {
			context.String(http.StatusOK, "ok")
		} else {
			context.String(http.StatusInternalServerError, "%v", err)
		}
	})

	route.GET("/del", func(context *gin.Context) {
		key := context.Query("key")
		if key == "" {
			context.String(http.StatusBadRequest, "miss key")
			return
		}
		if err := level.DelString(key); err == nil {
			context.String(http.StatusOK, "ok")
		} else {
			context.String(http.StatusInternalServerError, "%v", err)
		}
	})

	hlog.Infof("hdb init success")
	return nil
}

func Run() error {
	return route.Run(config.GetString("address"))
}
