package command

import "fmt"

//MotherBoard receiver
type MotherBoard struct{}

func (*MotherBoard) Start() {
	fmt.Print("system starting\n")
}

func (*MotherBoard) Reboot() {
	fmt.Print("system rebooting\n")
}

//Command 命令
type Command interface {
	Execute()
}

// StartCommand 具体的开始命令
type StartCommand struct {
	mb *MotherBoard
}

func NewStartCommand(mb *MotherBoard) *StartCommand {
	return &StartCommand{
		mb: mb,
	}
}

func (c *StartCommand) Execute() {
	c.mb.Start()
}

// RebootCommand 重启，具体的命令
type RebootCommand struct {
	mb *MotherBoard
}

func NewRebootCommand(mb *MotherBoard) *RebootCommand {
	return &RebootCommand{
		mb: mb,
	}
}

func (c *RebootCommand) Execute() {
	c.mb.Reboot()
}

//MacroCommand 命令管理
type MacroCommand struct {
	commands []Command
}

func (mc *MacroCommand) Execute() string {
	var result string
	for _, command := range mc.commands {
		command.Execute()
	}
	return result
}

func (mc *MacroCommand) append(command Command) {
	mc.commands = append(mc.commands, command)
}

func (mc *MacroCommand) Undo() {
	if len(mc.commands) != 0 {
		mc.commands = mc.commands[:len(mc.commands)]
	}
}

func (mc *MacroCommand) Clear() {
	mc.commands = []Command{}
}
