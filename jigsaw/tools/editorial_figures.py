#!/usr/bin/env python3
"""Draws the SVG figures of the editorial (zig-zag decompositions)."""
import math, os, sys
out = sys.argv[1]
COL = ["#2563eb", "#dc2626", "#16a34a", "#d97706", "#7c3aed"]

def circle_pts(m, R=110, cx=150, cy=150):
    return [(cx + R * math.sin(2 * math.pi * k / m), cy - R * math.cos(2 * math.pi * k / m)) for k in range(m)]

def zig(i, m):
    h = m // 2; z = [i]
    for k in range(1, h + 1):
        z.append((i + k) % m)
        if k < h: z.append((i - k) % m)
    return z

def svg(paths, pts, labels, extra_pts=None, title=""):
    s = ['<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 300 320" width="300" height="320" font-family="DejaVu Sans" font-size="13">']
    for ci, p in enumerate(paths):
        d = " ".join(("M" if j == 0 else "L") + f"{pts[v][0]:.1f},{pts[v][1]:.1f}" for j, v in enumerate(p))
        s.append(f'<path d="{d}" fill="none" stroke="{COL[ci % len(COL)]}" stroke-width="3" stroke-linejoin="round" opacity="0.85"/>')
    for k, (x, y) in enumerate(pts):
        s.append(f'<circle cx="{x:.1f}" cy="{y:.1f}" r="13" fill="white" stroke="#111" stroke-width="1.5"/>')
        s.append(f'<text x="{x:.1f}" y="{y+4.5:.1f}" text-anchor="middle">{labels[k]}</text>')

    s.append('</svg>')
    return "\n".join(s)

# Figure 1: n = 6, three zig-zag Hamiltonian paths partition K6
m = 6; pts = circle_pts(m)
open(os.path.join(out, "zigzag6.svg"), "w").write(
    svg([zig(i, m) for i in range(m // 2)], pts, [str(k + 1) for k in range(m)], title="n = 6 : 3 paths cover all 15 edges"))

# Figure 2: n = 7, circle of 6 + infinity in the centre, three Hamiltonian cycles
m = 6; pts = circle_pts(m) + [(150, 150)]
cyc = [[6] + zig(i, m) + [6] for i in range(m // 2)]
open(os.path.join(out, "walecki7.svg"), "w").write(
    svg(cyc, pts, [str(k + 1) for k in range(m)] + ["7"], title="n = 7 : 3 Hamiltonian cycles through 7"))
