import React from 'react';
import { BookOpen, Code, Cpu, ShieldCheck } from 'lucide-react';

export const DocsView: React.FC = () => {
  return (
    <div style={{ padding: '24px', maxWidth: '900px', margin: '0 auto', height: '100%', overflowY: 'auto' }}>
      <h1 style={{ fontSize: '22px', fontWeight: 700, marginBottom: 8, color: 'var(--text-primary)' }}>
        Compiler Studio Reference Manual & Viva Guide
      </h1>
      <p style={{ color: 'var(--text-secondary)', fontSize: '13px', marginBottom: 24 }}>
        Course: Compiler Design Lab (BCSE307P) — Design and Development of a Compiler for Structured Control Flow Using Three-Address Code and Backpatching.
      </p>

      {/* Grammar Section */}
      <div style={{ background: 'var(--bg-secondary)', padding: '16px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)', marginBottom: 20 }}>
        <h2 style={{ fontSize: '15px', fontWeight: 600, marginBottom: 12, display: 'flex', alignItems: 'center', gap: 8, color: 'var(--accent-blue)' }}>
          <Code size={16} /> Formal Context-Free Grammar (BNF)
        </h2>
        <pre className="mono" style={{ fontSize: '12px', background: 'var(--bg-primary)', padding: '12px', borderRadius: 'var(--radius-sm)', overflowX: 'auto', lineHeight: 1.5 }}>
{`PROG    -> S_LIST
S_LIST  -> S_LIST M S | S
M       -> ε                    { M.quad = nextquad() }
N       -> ε                    { N.nextlist = makelist(nextquad()); emit("goto", "", "", "_"); }
S       -> ID = E ;
         | print ( E ) ;
         | print ( STRING_LITERAL ) ;
         | if ( C ) M { S_LIST }
         | if ( C ) M { S_LIST } else N M { S_LIST }
         | while ( M C ) M { S_LIST }
         | for ( FOR_INIT ; M C ; M FOR_STEP ) M { S_LIST }
         | { S_LIST }
C       -> ( C ) | E < E | E > E | E <= E | E >= E | E == E | E != E
E       -> ( E ) | E + E | E - E | E * E | E / E | ID | NUM`}
        </pre>
      </div>

      {/* Backpatching Explanation */}
      <div style={{ background: 'var(--bg-secondary)', padding: '16px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)', marginBottom: 20 }}>
        <h2 style={{ fontSize: '15px', fontWeight: 600, marginBottom: 12, display: 'flex', alignItems: 'center', gap: 8, color: 'var(--accent-green)' }}>
          <BookOpen size={16} /> Backpatching Algorithm & List Operations
        </h2>
        <div style={{ fontSize: '13px', color: 'var(--text-primary)', lineHeight: 1.6, display: 'flex', flexDirection: 'column', gap: 8 }}>
          <p>
            <strong>Problem:</strong> When generating intermediate code for branches (e.g. <code>if (x &lt; 5) goto _</code>), the target jump destination is not yet known in a single-pass syntax-directed translation.
          </p>
          <p>
            <strong>Solution (Backpatching):</strong> Maintain lists of instructions whose jump targets are incomplete:
          </p>
          <ul style={{ paddingLeft: '20px' }}>
            <li><code>makelist(quad_index)</code>: Creates a new linked list containing a single instruction index with an unresolved target.</li>
            <li><code>merge(list1, list2)</code>: Concatenates two unresolved target lists.</li>
            <li><code>backpatch(list, target_quad)</code>: Traverses the list and fills in the actual target quad number into the result/destination field of each pending instruction.</li>
          </ul>
        </div>
      </div>

      {/* Basic Blocks & Leader Rules */}
      <div style={{ background: 'var(--bg-secondary)', padding: '16px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)', marginBottom: 20 }}>
        <h2 style={{ fontSize: '15px', fontWeight: 600, marginBottom: 12, display: 'flex', alignItems: 'center', gap: 8, color: 'var(--accent-purple)' }}>
          <Cpu size={16} /> Basic Block Partitioning (Leader Rules)
        </h2>
        <div style={{ fontSize: '13px', color: 'var(--text-primary)', lineHeight: 1.6 }}>
          A sequence of consecutive instructions where control enters only at the beginning and leaves only at the end without halting or branching except at the last instruction.
          <br /><br />
          <strong>Leader Algorithm:</strong>
          <ol style={{ paddingLeft: '20px', marginTop: '6px' }}>
            <li>The first instruction (quad #0) is a leader.</li>
            <li>Any instruction that is the target of a conditional or unconditional jump is a leader.</li>
            <li>Any instruction that immediately follows a conditional or unconditional jump is a leader.</li>
          </ol>
        </div>
      </div>
    </div>
  );
};
