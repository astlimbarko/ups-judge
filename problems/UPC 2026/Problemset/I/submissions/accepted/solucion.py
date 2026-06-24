import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    s = input().strip()
    n = len(s)
    
    # If there are two adjacent '*' cells, Monocarp can go back and forth infinitely
    # Also if there's a '*' at position 0 or n-1, he has one side blocked
    # Check for infinite: two adjacent '*', or '>*', '*<', '><'
    # Actually:
    # - If there are two adjacent '*' => infinite (bounce between them)
    # - If there's '*>' or '<*' => can go into * and back
    # - The key: Monocarp can navigate infinitely iff there exist adjacent cells
    #   where he can oscillate. This happens when:
    #   - Two adjacent '*' (can freely go back and forth)
    #   - '*' followed by '<' (go left from *, current carries right, come back)
    #   Actually let me think more carefully...
    #
    # Monocarp moves:
    # - On '*': he CHOOSES direction (left or right)
    # - On '<': forced left
    # - On '>': forced right
    #
    # Infinite if he can create a loop:
    # - Two adjacent '*': start on one, go to other, go back, repeat => infinite
    # - '*' and '<' where * is right of <: no...
    # - '>' followed by '*': from >, forced right to *, from * go left to >, forced right again... wait
    #   that's ><... no, it's > then *. From > he goes right to *. From * he goes left to >. From > forced right to *. INFINITE!
    # - '<' preceded by '*': from * go right to <, from < forced left to *. From * go right to <. INFINITE!
    # - But also '><': from > go right? No > at position i means forced right to i+1. If i+1 is <, forced left to i which is >. INFINITE!
    # 
    # So infinite conditions:
    # - Any pair of adjacent cells where you can loop:
    #   - '**', '>*', '*<', '><'
    #   Wait, '>*': from > forced to *, from * you choose LEFT, back to >, forced to * again. INFINITE
    #   '*<': from * you choose RIGHT, go to <, forced LEFT back to *. INFINITE
    #   '><': from > forced RIGHT to <, forced LEFT to >. INFINITE
    #   '**': from * choose RIGHT to *, choose LEFT to *. INFINITE
    #
    # So infinite iff there exist adjacent cells (i, i+1) where s[i] in '>*' and s[i+1] in '<*'
    
    infinite = False
    for i in range(n - 1):
        if s[i] in '>*' and s[i+1] in '<*':
            infinite = True
            break
    
    if infinite:
        print(-1)
    else:
        # If not infinite, every starting position eventually leads to shore
        # Find maximum time to reach shore from any starting position
        # Since no infinite loops, the river has structure: all '>' or '<' or isolated '*'
        # with no two adjacent that allow loops.
        # Given no '>*', '*<', '><', '**' pairs:
        # The only valid adjacent pairs are: '><' NOT allowed, '>>' allowed, '<<' allowed, 
        # '>*' NOT allowed... wait we said these make infinite
        # Remaining valid pairs: '>>', '<<', '<>', '<*'... wait
        # s[i] NOT in '>*' or s[i+1] NOT in '<*' for all i
        # So for each i: NOT(s[i] in '>*' AND s[i+1] in '<*')
        # Meaning: if s[i] is '>' or '*', then s[i+1] must be '>'
        # And: if s[i+1] is '<' or '*', then s[i] must be '<'
        # 
        # This means the string looks like: some '<'s, possibly a '>' at the boundary, then '>'s
        # Actually it means: all '*' are isolated with '>' on left or '<' on right only
        # Simpler: just simulate from each position
        
        max_time = 0
        for start in range(n):
            pos = start
            time = 0
            while 0 <= pos < n:
                if s[pos] == '<':
                    pos -= 1
                elif s[pos] == '>':
                    pos += 1
                else:  # '*'
                    # Choose direction that maximizes time
                    # Try both and pick max - but since no infinite loops, both are finite
                    # Actually in the non-infinite case, from a * we know:
                    # s[pos-1] must be '<' or pos==0 (otherwise s[pos-1] in '>*' and s[pos] in '<*')
                    # s[pos+1] must be '>' or pos==n-1
                    # So from *, going left hits '<' or shore, going right hits '>' or shore
                    # Going left: pos-1 is '<' -> goes further left -> eventually shore (quick)
                    # Going right: pos+1 is '>' -> goes further right -> eventually shore (quick)
                    # The longer path is going in the direction of more cells
                    # Since it won't loop, pick direction that leads farther from shore
                    # To keep it simple: try both
                    # But nested simulation would be complex. Let's just try both and pick max.
                    # Actually, since no infinite case, each * has unique outcome:
                    # go left -> shore. go right -> shore. Pick longer.
                    # Simulate both from this starting position
                    break  # handle below
                time += 1
            
            if 0 <= pos < n and s[pos] == '*':
                # Try both directions from starting position
                # Left
                t1 = time
                p = pos - 1
                t1 += 1
                while 0 <= p < n:
                    if s[p] == '<':
                        p -= 1
                    elif s[p] == '>':
                        p += 1
                    else:
                        p -= 1  # shouldn't happen in non-infinite case but fallback
                    t1 += 1
                # Right
                t2 = time
                p = pos + 1
                t2 += 1
                while 0 <= p < n:
                    if s[p] == '<':
                        p -= 1
                    elif s[p] == '>':
                        p += 1
                    else:
                        p += 1
                    t2 += 1
                max_time = max(max_time, t1, t2)
            else:
                max_time = max(max_time, time)
        
        print(max_time)
