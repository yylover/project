package main

import "fmt"

//AdvancedMediaPlayer
type AdvancedMediaPlayer interface {
	playVlc(filename string)
	playMp4(filename string)
}

//ConcreateProductA implement interface ProductParent
type VlcPlayer struct {
}

func (*VlcPlayer) playVlc(filename string) {
	fmt.Println("playVlc")
}
func (*VlcPlayer) playMp4(filename string) {

}

//Mp4Player 具体的mp4播放器
type Mp4Player struct {
}

func (*Mp4Player) playVlc(filename string) {

}
func (*Mp4Player) playMp4(filename string) {
	fmt.Println("playMp4")
}

//MediaPlayer 具体的使用接口
type MediaPlayer interface {
	play(audioType string, fileName string)
}

//MediaAdapter 具体的适配器
type MediaAdapter struct {
	player AdvancedMediaPlayer
}

func NewMediaApapter(audioType string) *MediaAdapter {
	if audioType != "vlc" && audioType != "mp4" {
		return nil
	}

	m := &MediaAdapter{}
	if audioType == "vlc" {
		m.player = &VlcPlayer{}
	} else {
		m.player = &Mp4Player{}
	}
	return m
}

func (m *MediaAdapter) play(audioType string, fileName string) {
	if audioType == "vlc" {
		m.player.playVlc(fileName)
	} else {
		m.player.playMp4(fileName)
	}
}

//AudioPlayer 接口实体类
type AudioPlayer struct {
	adapter *MediaAdapter
}

func (a *AudioPlayer) play(audioType string, fileName string) {
	if audioType == "mp3" {
		fmt.Println("play mp3 self")
	} else if audioType == "vlc" || audioType == "mp4" {
		a.adapter.play(audioType, fileName)
	} else {
		fmt.Println("Invalid audio type")
	}
}

func main() {
	audioPlayer := &AudioPlayer{}
	audioPlayer.adapter = NewMediaApapter("vlc")

	audioPlayer.play("mp3", "test.mp3")
	audioPlayer.play("vlc", "test.mp3")
	audioPlayer.play("mp4", "test.mp3")
	audioPlayer.play("cav", "test.mp3")
}
