package main

import (
	"fmt"
	"github.com/cihub/seelog"
	"github.com/spf13/viper"
	"gopkg.in/mgo.v2"
	"net/http"
)

func init() {
	viper.SetDefault("mongo.url", "127.0.0.1:27017")
	viper.SetDefault("mongo.database", "httpdb")
	viper.SetDefault("mongo.collection", "kv")
}

func main() {
	http.HandleFunc("/mongo/set", func(w http.ResponseWriter, req *http.Request) {
		key := req.FormValue("key")
		val := req.FormValue("val")
		if key == "" || val == "" {
			message := fmt.Sprintf("miss key or value. %s", req.URL)
			w.WriteHeader(500)
			w.Write([]byte(message))
			seelog.Warn(message)
			return
		}

		session, err := mgo.Dial(viper.GetString("mongo.url"))
		if err != nil {
			message := fmt.Sprintf("dial mgo[%s] failed. %s", viper.GetString("mongo.url"), err)
			w.WriteHeader(500)
			w.Write([]byte(message))
			seelog.Warnf(message)
			return
		}

		collection := session.DB(viper.GetString("mongo.database")).C(viper.GetString("mongo.collection"))

		if collection.FindId(key).One(nil) != nil {
			err = collection.Insert(map[string]string{"_id": key, "val": val})
		} else {
			err = collection.UpdateId(key, map[string]string{"val": val})
		}
		if err != nil {
			message := fmt.Sprintf(`%s.%s.insert({"_id": "%s", "val": "%s"}) failed. %s`,
				viper.GetString("mongo.database"), viper.GetString("mongo.collection"), key, val, err,
			)
			w.WriteHeader(500)
			w.Write([]byte(message))
			seelog.Warn(message)
			return
		}
		message := fmt.Sprintf("ok set %s => %s", key, val)
		w.WriteHeader(200)
		w.Write([]byte(message))
		seelog.Info(message)
	})

	http.ListenAndServe(":7000", nil)
}
