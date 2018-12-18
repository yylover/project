package main

import (
    "fmt"
)

type Pet struct {
    speaker func() string
    name    string
}

type Dog struct {
    Pet
    Breed string
}

func NewPet(name string) *Pet {
    p := &Pet{
        name: name,
    }
    p.speaker = p.speak
    return p
}

func (p *Pet) Play() {
    fmt.Println(p.Speak())
}

func (p *Pet) Speak() string {
    return p.speaker()
}

func (p *Pet) speak() string {
    return fmt.Sprintf("my name is %v", p.name)
}

func (p *Pet) Name() string {
    return p.name
}

func NewDog(name, breed string) *Dog {
    d := &Dog{
        Pet:   Pet{name: name},
        Breed: breed,
    }
    d.speaker = d.speak
    return d
}

func (d *Dog) speak() string {
    return fmt.Sprintf("%v and I am a %v", d.Pet.speak(), d.Breed)
}

func main() {
    d := NewDog("spot", "pointer")
    fmt.Println(d.Name())
    fmt.Println(d.Speak())
    d.Play()
}