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
			
				dirName:= strings.Trim(splitName[1], ".jpg")
				fmt.Println("Dir: " + dirName)
				
				if _, err := os.Stat(dirName); os.IsNotExist(err) {
					fmt.Println("Create Dir: " + dirName)
					os.Mkdir(dirName, 0)
				}
				
				dest :=  "./" + dirName + "/" + f.Name()
				os.Rename("./" + f.Name(), dest)
			}
    }
}