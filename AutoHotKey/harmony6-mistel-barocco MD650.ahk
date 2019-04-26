#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
;UseHook On

;;#Include sands0.ahk

; QWERTY to Harmony6 mapping

; **** Windows ****
; set NumpadDiv to right SHIFT by remapkey.exe


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; default layer
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; ---- num row ----
7::\
8::6
9::7
0::8
-::9
=::0
Backspace::Send, {vkF3sc029}

;; ---- top row -----
;;q::'
;;w::,
e::r
r::n
t::f

y::'
u::j
i::u
o::o
p::l
[::p
]::BS
\::Delete

;; ---- home row ----
a::k
;;s::s
d::t
f::h
g::m

h::BS
j::g
k::i
l::e
`;::a
'::y
;;Enter::Enter

;; ---- bottom row ----
;;z::`;
;;x::q
;;c::j
;;v::k
;;b::x

n::Enter
m::-
,::d
.::,
/::.
NumpadDiv::/






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; layer 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CapsLock & j::Home
CapsLock & k::PgDn
CapsLock & l::PgUp
CapsLock & `;::End
CapsLock::Return
Space & CapsLock::CapsLock
Space & BackSpace::NumLock
Space & \::Ins
;;CapsLock & ,::Send,{vk1D}
;;CapsLock & .::Send,{vk1C}


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; layer 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Space & j::Left
Space & k::Down
Space & l::Up
Space & `;::Right
Space & Enter::ESC

Space & a::`;
Space & s::(
Space & d::)
Space & f::'
Space & x::[
Space & c::]
Space & m::=
Space & NumpadDiv::\
;;Space & g::BS
Space & g::`
Space & ]::ESC

Space::Space
;;Space::Return
