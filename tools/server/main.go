package main

import "github.com/gin-gonic/gin"
import "fmt"
import "io/ioutil"

func main() {

	gin.SetMode(gin.ReleaseMode)
	r := gin.Default()

	r.POST("/message", func(c *gin.Context) {
		req := c.Request
		body, err := ioutil.ReadAll(req.Body)
		if err != nil {
			return
		}
		payload := string(body)
		fmt.Println(payload)
		c.JSON(200, gin.H{
			"message": "ok",
		})
	})
	r.Run() // 监听并在 0.0.0.0:8080
}
