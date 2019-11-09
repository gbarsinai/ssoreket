package main

import (
    "fmt"
    "io/ioutil"
     "log"
	 "os"
	 "strings"
)

func main() {
    files, err := ioutil.ReadDir("./")
    if err != nil {
        log.Fatal(err)
    }

    for _, f := range files {
			splitName := strings.SplitAfterN(f.Name(), " ", 2)
			if len(splitName) == 2{			
			
				runes := []rune(splitName[1])
				dirName:= string(runes[0:4])
				
				
				
				if _, err := os.Stat(dirName); os.IsNotExist(err) {
					fmt.Println("Create Dir: " + dirName)
					os.Mkdir(dirName, 0)
				}
				
				dest :=  "./" + dirName + "/" + f.Name()
				os.Rename("./" + f.Name(), dest)
			}
    }
}