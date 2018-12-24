package main

import (
	"log"
	"github.com/golang/protobuf/proto"

	"proto_play/input"
)

func main() {
	test := &input.Test{
		Label: proto.String("hello proto"),
		Type: proto.Int32(17),
		Reps: []int64{1, 3, 4},
		FirstName: proto.String("Zhang"),
	}

	data, err := proto.Marshal(test)
	if err != nil {
		log.Fatal("marshaling error: ", err)
	}
	log.Println("data: ", data)

	newTest := &input.Test{}
	err = proto.Unmarshal(data, newTest)
	if err != nil {
		log.Fatal("unmarshaling error: ", err)
	}
	log.Println("newTest: ", newTest)

	// Now test and newTest contain the same data
	if test.GetLabel() != newTest.GetLabel() {
		log.Fatalf("data dismatch: %q != %q", test.GetLabel(), newTest.GetLabel())
	} else {
		log.Printf("data match: %q == %q\n", test.GetLabel(), newTest.GetLabel())
	}
}