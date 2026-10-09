import React, { useState, useEffect } from 'react';
import Editor from '@monaco-editor/react';
import {
  Code,
  Layers,
  GitMerge,
  Sparkles,
  Play,
  Cpu,
  CheckSquare,
  BookOpen,
  Sun,
  Moon,
  AlertCircle,
  FileCode,
  CheckCircle2,
} from 'lucide-react';

import { CFGStudio } from './components/CFGStudio';
import { IRExplorer } from './components/IRExplorer';
import { OptimizationLab } from './components/OptimizationLab';
import { VirtualExecution } from './components/VirtualExecution';
import { RegisterStudio } from './components/RegisterStudio';
import { TestBench } from './components/TestBench';
import { DocsView } from './components/DocsView';

import { CompilationResult, OptimizationResult, VMState } from './types';

export const App: React.FC = () => {
  const [theme, setTheme] = useState<'dark' | 'light'>('dark');
  const [activeTab, setActiveTab] = useState<
    'source' | 'ir' | 'cfg' | 'optimization' | 'execution' | 'registers' | 'testbench' | 'docs'
  >('source');

  // Source & Samples
  const [samples, setSamples] = useState<Record<string, { title: string; code: string; description: string }>>({});
  const [selectedSample, setSelectedSample] = useState<string>('test_nested.c');
  const [code, setCode] = useState<string>('');

  // Compiler state
  const [compilationResult, setCompilationResult] = useState<CompilationResult | null>(null);
  const [isCompiling, setIsCompiling] = useState<boolean>(false);
  const [selectedQuadId, setSelectedQuadId] = useState<number | undefined>(undefined);

  // Optimizer state
  const [optResult, setOptResult] = useState<OptimizationResult | null>(null);
  const [isOptimizing, setIsOptimizing] = useState<boolean>(false);

  // Virtual Machine state
  const [vmState, setVmState] = useState<VMState | null>(null);
  const [isVmRunning, setIsVmRunning] = useState<boolean>(false);

  // Fetch samples on load
  useEffect(() => {
    fetch('/api/samples')
      .then((res) => res.json())
      .then((data) => {
        setSamples(data);
        if (data['test_nested.c']) {
          setCode(data['test_nested.c'].code);
        }
      })
      .catch((e) => console.error('Failed to load samples:', e));
  }, []);

  // Theme switch effect
  useEffect(() => {
    document.documentElement.setAttribute('data-theme', theme);
  }, [theme]);

  // Load sample code
  const handleSelectSample = (sampleKey: string) => {
    setSelectedSample(sampleKey);
    if (samples[sampleKey]) {
      setCode(samples[sampleKey].code);
    }
  };

  // Compile
  const handleCompile = async () => {
    setIsCompiling(true);
    try {
      const res = await fetch('/api/compile', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ code }),
      });
      const data: CompilationResult = await res.json();
      setCompilationResult(data);
      setOptResult(null); // reset stale optimization

      // Initialize VM state
      if (data.quads && data.quads.length > 0) {
        const vmRes = await fetch('/api/execute/reset', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ quads: data.quads }),
        });
        const vmData = await vmRes.json();
        setVmState(vmData.state);
      }
    } catch (e) {
      console.error(e);
    } finally {
      setIsCompiling(false);
    }
  };

  // Optimize
  const handleApplyOptimization = async (passes: string[]) => {
    if (!compilationResult || !compilationResult.quads) return;
    setIsOptimizing(true);
    try {
      const res = await fetch('/api/optimize', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ quads: compilationResult.quads, passes }),
      });
      const data: OptimizationResult = await res.json();
      setOptResult(data);
    } catch (e) {
      console.error(e);
    } finally {
      setIsOptimizing(false);
    }
  };

  // VM Stepping
  const handleVmStep = async (direction: 'forward' | 'backward') => {
    try {
      const res = await fetch('/api/execute/step', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ direction }),
      });
      const data = await res.json();
      setVmState(data.state);
    } catch (e) {
      console.error(e);
    }
  };

  const handleVmRunAll = async () => {
    setIsVmRunning(true);
    try {
      const res = await fetch('/api/execute', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ quads: compilationResult?.quads }),
      });
      const data = await res.json();
      setVmState(data.state);
    } catch (e) {
      console.error(e);
    } finally {
      setIsVmRunning(false);
    }
  };

  const handleVmReset = async () => {
    try {
      const res = await fetch('/api/execute/reset', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ quads: compilationResult?.quads }),
      });
      const data = await res.json();
      setVmState(data.state);
    } catch (e) {
      console.error(e);
    }
  };

  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: '100vh', width: '100vw' }}>
      {/* Top Application Header */}
      <header
        style={{
          height: '46px',
          background: 'var(--bg-secondary)',
          borderBottom: '1px solid var(--border-color)',
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'space-between',
          padding: '0 16px',
        }}
      >
        <div style={{ display: 'flex', alignItems: 'center', gap: 10 }}>
          <Code size={20} style={{ color: 'var(--accent-blue)' }} />
          <span style={{ fontWeight: 700, fontSize: '15px', letterSpacing: '-0.3px' }}>
            COMPILER STUDIO
          </span>
          <span className="badge badge-blue">v2.0</span>
          <span style={{ fontSize: '12px', color: 'var(--text-muted)', marginLeft: 8 }}>
            Compiler Design Lab • BCSE307P
          </span>
        </div>

        {/* Global Compile Status & Actions */}
        <div style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
          {compilationResult && (
            <div style={{ display: 'flex', alignItems: 'center', gap: 8, fontSize: '12px' }}>
              {compilationResult.success ? (
                <span className="badge badge-green" style={{ display: 'inline-flex', gap: 4, alignItems: 'center' }}>
                  <CheckCircle2 size={12} /> COMPILED ({compilationResult.duration_ms}ms)
                </span>
              ) : (
                <span className="badge badge-red" style={{ display: 'inline-flex', gap: 4, alignItems: 'center' }}>
                  <AlertCircle size={12} /> {compilationResult.diagnostics.length} ERROR(S)
                </span>
              )}
            </div>
          )}

          <button className="btn btn-primary" onClick={handleCompile} disabled={isCompiling}>
            <Play size={14} /> {isCompiling ? 'Compiling...' : 'Compile Source'}
          </button>

          <button
            className="btn btn-secondary"
            onClick={() => setTheme(theme === 'dark' ? 'light' : 'dark')}
            title="Toggle theme"
          >
            {theme === 'dark' ? <Sun size={14} /> : <Moon size={14} />}
          </button>
        </div>
      </header>

      {/* Main Workspace Navigation Bar */}
      <nav
        style={{
          height: '38px',
          background: 'var(--bg-tertiary)',
          borderBottom: '1px solid var(--border-color)',
          display: 'flex',
          padding: '0 12px',
          gap: 4,
          alignItems: 'center',
        }}
      >
        <button
          onClick={() => setActiveTab('source')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'source' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'source' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <FileCode size={14} /> Source Workspace
        </button>

        <button
          onClick={() => setActiveTab('ir')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'ir' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'ir' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <Layers size={14} /> Intermediate Reps (IR)
        </button>

        <button
          onClick={() => setActiveTab('cfg')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'cfg' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'cfg' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <GitMerge size={14} /> Control-Flow Graph Studio
        </button>

        <button
          onClick={() => setActiveTab('optimization')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'optimization' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'optimization' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <Sparkles size={14} /> Optimization Lab
        </button>

        <button
          onClick={() => setActiveTab('execution')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'execution' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'execution' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <Play size={14} /> Virtual Execution
        </button>

        <button
          onClick={() => setActiveTab('registers')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'registers' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'registers' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <Cpu size={14} /> Register & Liveness
        </button>

        <button
          onClick={() => setActiveTab('testbench')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'testbench' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'testbench' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <CheckSquare size={14} /> Test Bench
        </button>

        <button
          onClick={() => setActiveTab('docs')}
          style={{
            padding: '6px 12px',
            borderRadius: 'var(--radius-sm)',
            fontSize: '12px',
            fontWeight: 600,
            display: 'flex',
            alignItems: 'center',
            gap: 6,
            background: activeTab === 'docs' ? 'var(--bg-secondary)' : 'transparent',
            color: activeTab === 'docs' ? 'var(--accent-blue)' : 'var(--text-secondary)',
          }}
        >
          <BookOpen size={14} /> Reference & Viva
        </button>
      </nav>

      {/* Main Workspace Body */}
      <main style={{ flex: 1, overflow: 'hidden' }}>
        {/* WORKSPACE 1: SOURCE EDITOR */}
        {activeTab === 'source' && (
          <div style={{ display: 'grid', gridTemplateColumns: '1fr 340px', height: '100%' }}>
            <div style={{ display: 'flex', flexDirection: 'column', height: '100%' }}>
              {/* Preset Selector */}
              <div
                style={{
                  padding: '8px 12px',
                  background: 'var(--bg-secondary)',
                  borderBottom: '1px solid var(--border-color)',
                  display: 'flex',
                  alignItems: 'center',
                  gap: 12,
                }}
              >
                <span style={{ fontSize: '12px', color: 'var(--text-muted)' }}>Load Preset:</span>
                <select
                  value={selectedSample}
                  onChange={(e) => handleSelectSample(e.target.value)}
                  style={{
                    padding: '4px 8px',
                    borderRadius: 'var(--radius-sm)',
                    background: 'var(--bg-tertiary)',
                    color: 'var(--text-primary)',
                    border: '1px solid var(--border-color)',
                    fontSize: '12px',
                    fontFamily: 'var(--font-sans)',
                  }}
                >
                  {Object.entries(samples).map(([k, s]) => (
                    <option key={k} value={k}>
                      {s.title} ({k})
                    </option>
                  ))}
                </select>
              </div>

              {/* Monaco Editor */}
              <div style={{ flex: 1 }}>
                <Editor
                  height="100%"
                  defaultLanguage="c"
                  theme={theme === 'dark' ? 'vs-dark' : 'light'}
                  value={code}
                  onChange={(val) => setCode(val || '')}
                  options={{
                    fontSize: 13,
                    fontFamily: 'JetBrains Mono, monospace',
                    minimap: { enabled: false },
                    scrollBeyondLastLine: false,
                    lineNumbers: 'on',
                    tabSize: 4,
                  }}
                />
              </div>
            </div>

            {/* Diagnostics & Tokens Sidebar */}
            <div
              style={{
                borderLeft: '1px solid var(--border-color)',
                background: 'var(--bg-secondary)',
                display: 'flex',
                flexDirection: 'column',
              }}
            >
              <div
                style={{
                  padding: '10px 14px',
                  background: 'var(--bg-tertiary)',
                  borderBottom: '1px solid var(--border-color)',
                  fontSize: '12px',
                  fontWeight: 600,
                  color: 'var(--text-secondary)',
                }}
              >
                COMPILER DIAGNOSTICS & TOKENS
              </div>

              {/* Diagnostics List */}
              <div style={{ flex: 1, overflowY: 'auto', padding: '12px' }}>
                {compilationResult?.diagnostics && compilationResult.diagnostics.length > 0 ? (
                  <div style={{ display: 'flex', flexDirection: 'column', gap: 8 }}>
                    {compilationResult.diagnostics.map((d, i) => (
                      <div
                        key={i}
                        style={{
                          padding: '8px 10px',
                          background: 'rgba(239, 68, 68, 0.1)',
                          borderLeft: '3px solid var(--accent-red)',
                          borderRadius: 'var(--radius-sm)',
                          fontSize: '12px',
                        }}
                      >
                        <div style={{ fontWeight: 600, color: 'var(--accent-red)', marginBottom: 2 }}>
                          {d.severity.toUpperCase()} at line {d.line}, col {d.col}
                        </div>
                        <div style={{ color: 'var(--text-primary)' }}>{d.message}</div>
                      </div>
                    ))}
                  </div>
                ) : (
                  <div style={{ fontSize: '12px', color: 'var(--accent-green)', display: 'flex', gap: 6, alignItems: 'center' }}>
                    <CheckCircle2 size={14} /> Zero errors. Source is syntactically valid.
                  </div>
                )}

                {/* Tokens List */}
                {compilationResult?.tokens && (
                  <div style={{ marginTop: 20 }}>
                    <div style={{ fontSize: '11px', fontWeight: 600, color: 'var(--text-muted)', marginBottom: 8 }}>
                      LEXICAL TOKENS STREAM ({compilationResult.tokens.length})
                    </div>
                    <div style={{ display: 'flex', flexDirection: 'column', gap: 4 }} className="mono">
                      {compilationResult.tokens.slice(0, 40).map((t) => (
                        <div
                          key={t.index}
                          style={{
                            fontSize: '11px',
                            display: 'flex',
                            justifyContent: 'space-between',
                            padding: '2px 4px',
                            background: 'var(--bg-tertiary)',
                            borderRadius: '2px',
                          }}
                        >
                          <span style={{ color: 'var(--accent-cyan)' }}>{t.type}</span>
                          <span style={{ color: 'var(--text-primary)' }}>{t.lexeme}</span>
                          <span style={{ color: 'var(--text-muted)' }}>L{t.line}</span>
                        </div>
                      ))}
                    </div>
                  </div>
                )}
              </div>
            </div>
          </div>
        )}

        {/* WORKSPACE 2: INTERMEDIATE CODE EXPLORER */}
        {activeTab === 'ir' && compilationResult && (
          <IRExplorer
            tac={compilationResult.tac}
            quads={compilationResult.quads}
            triples={compilationResult.triples}
            indirectTriples={compilationResult.indirect_triples}
            backpatchLogs={compilationResult.backpatch_logs}
            selectedQuadId={selectedQuadId}
            onSelectQuad={(id) => setSelectedQuadId(id)}
          />
        )}

        {/* WORKSPACE 3: CFG STUDIO */}
        {activeTab === 'cfg' && compilationResult && (
          <CFGStudio
            cfg={compilationResult.cfg}
            activeQuadId={selectedQuadId}
            onSelectBlock={(bId) => {}}
          />
        )}

        {/* WORKSPACE 4: OPTIMIZATION LAB */}
        {activeTab === 'optimization' && compilationResult && (
          <OptimizationLab
            quads={compilationResult.quads}
            onApplyOptimization={handleApplyOptimization}
            optResult={optResult}
            isLoading={isOptimizing}
          />
        )}

        {/* WORKSPACE 5: VIRTUAL EXECUTION */}
        {activeTab === 'execution' && compilationResult && (
          <VirtualExecution
            vmState={vmState}
            quads={compilationResult.quads}
            onStepForward={() => handleVmStep('forward')}
            onStepBackward={() => handleVmStep('backward')}
            onRunAll={handleVmRunAll}
            onReset={handleVmReset}
            isLoading={isVmRunning}
          />
        )}

        {/* WORKSPACE 6: REGISTER STUDIO */}
        {activeTab === 'registers' && compilationResult && (
          <RegisterStudio
            analysis={compilationResult.registers}
            quadCount={compilationResult.quads.length}
          />
        )}

        {/* WORKSPACE 7: TEST BENCH */}
        {activeTab === 'testbench' && <TestBench />}

        {/* WORKSPACE 8: DOCS & VIVA */}
        {activeTab === 'docs' && <DocsView />}
      </main>
    </div>
  );
};
