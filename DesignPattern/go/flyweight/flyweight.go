package flyweight

import "fmt"

type ImageFlyWeightFactory struct {
	maps map[string]*ImageFlyWeight
}

var imageFactory *ImageFlyWeightFactory

func GetImageFlyweightFacotry() *ImageFlyWeightFactory {
	if imageFactory == nil {
		imageFactory = &ImageFlyWeightFactory{
			maps: make(map[string]*ImageFlyWeight),
		}
	}
	return imageFactory
}

func (f *ImageFlyWeightFactory) Get(filename string) *ImageFlyWeight {
	image := f.maps[filename]
	if image == nil {
		image = NewImageFlyWeight(filename)
		f.maps[filename] = image
	}
	return image
}

type ImageFlyWeight struct {
	data string
}

func NewImageFlyWeight(filename string) *ImageFlyWeight {
	data := fmt.Sprintf("image data %s", filename)
	return &ImageFlyWeight{
		data: data,
	}
}

func (i *ImageFlyWeight) Data() string {
	return i.data
}

//Viewer
type ImageViewer struct {
	*ImageFlyWeight
}

func NewImageViewer(filename string) *ImageViewer {
	image := GetImageFlyweightFacotry().Get(filename)
	return &ImageViewer{
		ImageFlyWeight: image,
	}
}

func (i *ImageViewer) Display() {
	fmt.Printf("Display %s\n", i.Data())
}
