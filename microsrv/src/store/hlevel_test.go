package store

import (
	"fmt"
	"testing"
)

var rtaLevel *HLevel

func init() {
	rtaLevel = &HLevel{}
	rtaLevel.Init("../../data/leveldb/")
}

func TestRtaLevel_GetString(t *testing.T) {
	rtaLevel.GetString("name")
}

func TestRtaLevel_PutString(t *testing.T) {
	if err := rtaLevel.PutString("name", "hatlonely"); err != nil {
		t.Errorf("put failed. err: [%v]", err)
	}
}

func TestRtaLevel_DelString(t *testing.T) {
	if err := rtaLevel.DelString("name"); err != nil {
		t.Errorf("del failed. err: [%v]", err)
	}
}

func TestRtaLevel_PutStringBatch(t *testing.T) {
	rtaLevel.PutStringBatch(&[]string{"name", "mail"}, &[]string{"hatlonely", "hatlonely@foxmail.com"})

	if val, err := rtaLevel.GetString("name"); err != nil || val != "hatlonely" {
		t.Errorf("execpted (hatlonely, nil), but (%s, %T) returned", val, err)
	}

	if val, err := rtaLevel.GetString("mail"); err != nil || val != "hatlonely@foxmail.com" {
		t.Errorf("execpted (hatlonely@foxmail.com, nil), but (%s, %T) returned", val, err)
	}
}

func TestRtaLevel_DelStringBatch(t *testing.T) {
	if err := rtaLevel.DelStringBatch(&[]string{"name", "mail"}); err != nil {
		t.Error("del batch failed.")
	}
}

func TestRtaLevel_Scan(t *testing.T) {
	rtaLevel.PutString("one", "1")
	rtaLevel.PutString("two", "2")
	rtaLevel.PutString("ten", "10")
	rtaLevel.Scan(func(key []byte, val []byte) {
		//t.Log(string(key), "=>", string(val))
	})
}

func TestRtaLevel_Concurrent(t *testing.T) {
	done := make(chan bool, 30)
	for i := 0; i < 10; i++ {
		go func() {
			for j := 0; j < 100; j++ {
				rtaLevel.PutString(fmt.Sprintf("key%d", i*100+j), fmt.Sprintf("val%d", i*100+j))
			}
			done <- true
		}()
	}
	for i := 0; i < 10; i++ {
		go func() {
			for j := 0; j < 100; j++ {
				rtaLevel.DelString(fmt.Sprintf("key%d", i*100+j))
			}
			done <- true
		}()
	}
	for i := 0; i < 10; i++ {
		go func() {
			for j := 0; j < 100; j++ {
				rtaLevel.GetString(fmt.Sprintf("key%d", i*100+j))
			}
			done <- true
		}()
	}

	for i := 0; i < 30; i++ {
		<-done
	}
}
