option casemap:none
option elfpic:1
extern ext_hidden:proc
option elfvisibility:ext_hidden:hidden
public default_data, hidden_data, protected_data
option elfvisibility:default_data:default
option elfvisibility:hidden_data:hidden
option elfvisibility:protected_data:protected
.data
default_data dq 1
hidden_data dq 2
protected_data dq 3
.code
 call ext_hidden
end
