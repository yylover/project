package builder

import "testing"

func TestBuild1(t *testing.T) {
	builder1 := &Builder1{}
	d := NewDirector(builder1)
	d.Construct()

	if d.part1 != "Builder1_A" {
		t.Fatal("Build1 PartA test failed")
	}

	if d.part2 != "Builder1_B" {
		t.Fatal("Build1 PartA test failed")
	}

	if d.part3 != "Builder1_C" {
		t.Fatal("Build1 PartA test failed")
	}
}

func TestBuild2(t *testing.T) {
	builder1 := &Builder2{}
	d := NewDirector(builder1)
	d.Construct()

	if d.part1 != "Builder2_A" {
		t.Fatal("Build2 PartA test failed")
	}

	if d.part2 != "Builder2_B" {
		t.Fatal("Build2 PartA test failed")
	}

	if d.part3 != "Builder2_C" {
		t.Fatal("Build2 PartA test failed")
	}
}
