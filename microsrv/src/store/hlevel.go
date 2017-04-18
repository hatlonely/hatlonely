package store

import (
	"errors"
	"fmt"
	"github.com/syndtr/goleveldb/leveldb"
	"sync"
)

type HLevel struct {
	db    *leveldb.DB
	mutex *sync.RWMutex
}

func (rl *HLevel) Init(dbpath string) error {
	db, err := leveldb.OpenFile(dbpath, nil)
	if err != nil {
		return err
	}
	rl.db = db
	rl.mutex = &sync.RWMutex{}

	return nil
}

func (rl *HLevel) Close() error {
	return rl.db.Close()
}

func (rl *HLevel) Scan(run func(key []byte, val []byte)) {
	rl.mutex.Lock()
	defer rl.mutex.Unlock()
	it := rl.db.NewIterator(nil, nil)
	for it.Next() {
		run(it.Key(), it.Value())
	}
}

func (rl *HLevel) Get(key []byte) ([]byte, error) {
	rl.mutex.RLock()
	defer rl.mutex.RUnlock()
	return rl.db.Get(key, nil)
}

func (rl *HLevel) Put(key []byte, val []byte) error {
	rl.mutex.Lock()
	defer rl.mutex.Unlock()
	return rl.db.Put(key, val, nil)
}

func (rl *HLevel) Del(key []byte) error {
	rl.mutex.Lock()
	defer rl.mutex.Unlock()
	return rl.db.Delete(key, nil)
}

func (rl *HLevel) PutBatch(keys *[][]byte, vals *[][]byte) error {
	if len(*keys) != len(*vals) {
		return errors.New(fmt.Sprintf("len(keys)[%d] != len(vals)[%d]", len(*keys), len(*vals)))
	}
	for i := 0; i < len(*keys); i++ {
		batch := &leveldb.Batch{}
		for j := 0; i < len(*keys) && j < 100; j++ {
			batch.Put((*keys)[i], (*vals)[i])
			i++
		}
		rl.mutex.Lock()
		err := rl.db.Write(batch, nil)
		rl.mutex.Unlock()
		if err != nil {
			return err
		}
	}

	return nil
}

func (rl *HLevel) DelBatch(keys *[][]byte) error {
	for i := 0; i < len(*keys); i++ {
		batch := &leveldb.Batch{}
		for j := 0; i < len(*keys) && j < 100; j++ {
			batch.Delete((*keys)[i])
			i++
		}
		rl.mutex.Lock()
		err := rl.db.Write(batch, nil)
		rl.mutex.Unlock()
		if err != nil {
			return err
		}
	}

	return nil
}

func (rl *HLevel) GetString(key string) (string, error) {
	rl.mutex.RLock()
	defer rl.mutex.RUnlock()
	val, err := rl.db.Get([]byte(key), nil)
	return string(val), err
}

func (rl *HLevel) PutString(key string, val string) error {
	rl.mutex.Lock()
	defer rl.mutex.Unlock()
	return rl.db.Put([]byte(key), []byte(val), nil)
}

func (rl *HLevel) DelString(key string) error {
	rl.mutex.Lock()
	defer rl.mutex.Unlock()
	return rl.db.Delete([]byte(key), nil)
}

func (rl *HLevel) PutStringBatch(keys *[]string, vals *[]string) error {
	if len(*keys) != len(*vals) {
		return errors.New(fmt.Sprintf("len(keys)[%d] != len(vals)[%d]", len(*keys), len(*vals)))
	}
	for i := 0; i < len(*keys); i++ {
		batch := &leveldb.Batch{}
		for j := 0; i < len(*keys) && j < 100; j++ {
			batch.Put([]byte((*keys)[i]), []byte((*vals)[i]))
			i++
		}
		rl.mutex.Lock()
		err := rl.db.Write(batch, nil)
		rl.mutex.Unlock()
		if err != nil {
			return err
		}
	}

	return nil
}

func (rl *HLevel) DelStringBatch(keys *[]string) error {
	for i := 0; i < len(*keys); i++ {
		batch := &leveldb.Batch{}
		for j := 0; i < len(*keys) && j < 100; j++ {
			batch.Delete([]byte((*keys)[i]))
			i++
		}
		rl.mutex.Lock()
		err := rl.db.Write(batch, nil)
		rl.mutex.Unlock()
		if err != nil {
			return err
		}
	}

	return nil
}
